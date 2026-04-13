#include "SquallyEquipmentVisualBehavior.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>

#include "2d/CCActionInterval.h"
#include "2d/CCRenderTexture.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "renderer/CCRenderer.h"

#include "GameWindow.h"
#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityWeaponCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Resources/MapResources.h"

using namespace cocos2d;

namespace
{
	const std::string OffsetLabValidationItemKey = "unarmed";
	const bool OffsetLabValidationStartsInDirectLayout = true;
	const Vec2 OffsetLabUnarmedCollisionOffset = Vec2(24.0f, 0.0f);

	std::string getOffsetLabValidationMapResource()
	{
		return "Public/Platformer/Maps/Dev/AnimSeq.tmx";
	}

	bool isOffsetLabUnarmedItemKey(const std::string& itemKey)
	{
		return itemKey == "unarmed";
	}

	void appendOffsetLabDebugLine(const std::string& line)
	{
		const std::string outputFilePath = FileUtils::getInstance()->getWritablePath() + "OffsetLabDebug.txt";
		std::ofstream stream(outputFilePath, std::ios::app);

		if (stream.is_open())
		{
			stream << line << "\n";
		}
	}

	std::string sanitizeArtifactName(const std::string& input)
	{
		std::string result = input;

		for (char& next : result)
		{
			const bool isAlphaNumeric = (next >= 'a' && next <= 'z')
				|| (next >= 'A' && next <= 'Z')
				|| (next >= '0' && next <= '9');
			const bool isAllowedPunctuation = next == '-' || next == '_';

			if (!isAlphaNumeric && !isAllowedPunctuation)
			{
				next = '_';
			}
		}

		return result;
	}

	void writeU16(std::ofstream& stream, std::uint16_t value)
	{
		stream.put(char(value & 0xff));
		stream.put(char((value >> 8) & 0xff));
	}

	void writeU32(std::ofstream& stream, std::uint32_t value)
	{
		stream.put(char(value & 0xff));
		stream.put(char((value >> 8) & 0xff));
		stream.put(char((value >> 16) & 0xff));
		stream.put(char((value >> 24) & 0xff));
	}

	void writeS32(std::ofstream& stream, std::int32_t value)
	{
		writeU32(stream, static_cast<std::uint32_t>(value));
	}

	bool saveImageAsBmp(Image* image, const std::string& outputFilePath)
	{
		if (image == nullptr || image->getData() == nullptr || image->getWidth() <= 0 || image->getHeight() <= 0)
		{
			return false;
		}

		const std::int32_t width = image->getWidth();
		const std::int32_t height = image->getHeight();
		const std::uint32_t pixelDataSize = std::uint32_t(width * height * 4);
		const std::uint32_t fileSize = 54u + pixelDataSize;

		std::ofstream stream(outputFilePath, std::ios::binary | std::ios::trunc);

		if (!stream.is_open())
		{
			return false;
		}

		stream.put('B');
		stream.put('M');
		writeU32(stream, fileSize);
		writeU16(stream, 0);
		writeU16(stream, 0);
		writeU32(stream, 54);
		writeU32(stream, 40);
		writeS32(stream, width);
		writeS32(stream, -height);
		writeU16(stream, 1);
		writeU16(stream, 32);
		writeU32(stream, 0);
		writeU32(stream, pixelDataSize);
		writeS32(stream, 2835);
		writeS32(stream, 2835);
		writeU32(stream, 0);
		writeU32(stream, 0);

		const unsigned char* rgba = image->getData();

		for (std::int32_t index = 0; index < width * height; index++)
		{
			const int pixelIndex = index * 4;
			stream.put(char(rgba[pixelIndex + 2]));
			stream.put(char(rgba[pixelIndex + 1]));
			stream.put(char(rgba[pixelIndex + 0]));
			stream.put(char(rgba[pixelIndex + 3]));
		}

		return stream.good();
	}
}

const bool SquallyEquipmentVisualBehavior::InvertDebugControls = true;
const float SquallyEquipmentVisualBehavior::DebugNudgeAmount = 2.0f;
const float SquallyEquipmentVisualBehavior::DebugPrecisionNudgeAmount = 0.5f;

const std::string SquallyEquipmentVisualBehavior::MapKey = "squally-equipment-visuals";

SquallyEquipmentVisualBehavior* SquallyEquipmentVisualBehavior::create(GameObject* owner)
{
	SquallyEquipmentVisualBehavior* instance = new SquallyEquipmentVisualBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyEquipmentVisualBehavior::SquallyEquipmentVisualBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->debugHud = Node::create();
	this->debugHudStr = ConstantString::create("");
	this->debugHudLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Monospaced, LocalizedLabel::FontSize::Tiny, this->debugHudStr, CSize(960.0f, 0.0f));
	
	this->debugHud->setVisible(false);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->debugHudLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->debugHudLabel->enableOutline(Color4B::BLACK, 2);
	this->debugHud->addChild(this->debugHudLabel);
	this->addChild(this->debugHud);
}

SquallyEquipmentVisualBehavior::~SquallyEquipmentVisualBehavior()
{
}

void SquallyEquipmentVisualBehavior::initializePositions()
{
	super::initializePositions();
	
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->debugHudLabel->setPosition(Vec2(24.0f, visibleSize.height - 24.0f));
}

void SquallyEquipmentVisualBehavior::onLoad()
{
	const std::string ownerMap = GameUtils::getKeyOrDefault(this->owner->properties, GameObject::MapKeyMetaMapIdentifier, Value("")).asString();
	const std::string saveMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();
	const std::string respawnMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value("")).asString();
	appendOffsetLabDebugLine("[OffsetLab][debug] onLoad ownerMap=" + ownerMap
		+ " saveMap=" + saveMap
		+ " respawnMap=" + respawnMap
		+ " target=" + getOffsetLabValidationMapResource()
		+ " ownerMatch=" + std::string(ownerMap == getOffsetLabValidationMapResource() ? "true" : "false")
		+ " saveMatch=" + std::string(saveMap == getOffsetLabValidationMapResource() ? "true" : "false")
		+ " respawnMatch=" + std::string(respawnMap == getOffsetLabValidationMapResource() ? "true" : "false")
		+ " ownerLen=" + std::to_string(ownerMap.size())
		+ " saveLen=" + std::to_string(saveMap.size())
		+ " respawnLen=" + std::to_string(respawnMap.size())
		+ " targetLen=" + std::to_string(getOffsetLabValidationMapResource().size())
		+ " isValidation=" + std::string(this->isOffsetLabValidationMap() ? "true" : "false"));

	this->squally->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		this->entityInventoryBehavior = entityInventoryBehavior;

		if (DeveloperModeController::IsDeveloperBuild)
		{
			this->initializeDebugEquipment();
			this->syncDebugSelectionToEquipment();
			this->initializeOffsetLabValidation();
			this->setEquipmentCompatibilityLayoutEnabled(this->debugCompatibilityLayoutEnabled);
			this->beginOffsetLabAutomation();
		}

		this->updateEquipmentVisual();
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		if (DeveloperModeController::IsDeveloperBuild)
		{
			this->syncDebugSelectionToEquipment();
		}

		this->updateEquipmentVisual();
	}));

	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->debugHud->setVisible(false);
		this->initializeDebugKeybindings();
		this->refreshDebugHud();
	}
}

void SquallyEquipmentVisualBehavior::initializeDebugEquipment()
{
	if (!this->debugWeaponKeys.empty() || !this->debugHatKeys.empty() || !this->debugOffhandKeys.empty())
	{
		return;
	}

	PlatformerItemDeserializer* itemDeserializer = PlatformerItemDeserializer::getInstance();

	for (const std::string& itemKey : itemDeserializer->getRegisteredItemKeys())
	{
		Item* item = itemDeserializer->createItem(itemKey);

		if (dynamic_cast<Weapon*>(item) != nullptr)
		{
			this->debugWeaponKeys.push_back(itemKey);
		}
		else if (dynamic_cast<Hat*>(item) != nullptr)
		{
			this->debugHatKeys.push_back(itemKey);
		}
		else if (dynamic_cast<Offhand*>(item) != nullptr)
		{
			this->debugOffhandKeys.push_back(itemKey);
		}
	}

	std::sort(this->debugWeaponKeys.begin(), this->debugWeaponKeys.end());
	std::sort(this->debugHatKeys.begin(), this->debugHatKeys.end());
	std::sort(this->debugOffhandKeys.begin(), this->debugOffhandKeys.end());

	this->debugWeaponKeys.insert(this->debugWeaponKeys.begin(), "");
	this->debugHatKeys.insert(this->debugHatKeys.begin(), "");
	this->debugOffhandKeys.insert(this->debugOffhandKeys.begin(), "");
}

void SquallyEquipmentVisualBehavior::initializeOffsetLabValidation()
{
	if (!this->isOffsetLabValidationMap() || this->entityInventoryBehavior == nullptr)
	{
		return;
	}

	EquipmentInventory* equipmentInventory = this->entityInventoryBehavior->getEquipmentInventory();

	if (equipmentInventory == nullptr)
	{
		return;
	}

	this->debugSelectedSlot = this->getDebugSlotForItem(OffsetLabValidationItemKey);
	this->debugOffsetsByItem.clear();
	this->debugWeaponCollisionOffsetsByItem.clear();
	this->debugOffsetTarget = this->debugSelectedSlot == DebugEquipmentSlot::Mainhand
		? DebugOffsetTarget::WeaponCollision
		: DebugOffsetTarget::Visual;
	this->debugCompatibilityLayoutEnabled = !OffsetLabValidationStartsInDirectLayout;
	this->debugHud->setVisible(false);
	DeveloperModeEvents::TriggerDeveloperModeModeEnable(DeveloperModeEvents::DeveloperModeEnableArgs(1));
	appendOffsetLabDebugLine("[OffsetLab][debug] init map detected savedMap=" + SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString()
		+ " respawnMap=" + SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value("")).asString()
		+ " weapon=" + std::string(equipmentInventory->getWeapon() == nullptr ? "<none>" : equipmentInventory->getWeapon()->getIdentifier()));

	this->enforceOffsetLabValidationEquipment(8);
}

void SquallyEquipmentVisualBehavior::enforceOffsetLabValidationEquipment(int remainingAttempts)
{
	if (!this->isOffsetLabValidationMap() || this->entityInventoryBehavior == nullptr)
	{
		return;
	}

	EquipmentInventory* equipmentInventory = this->entityInventoryBehavior->getEquipmentInventory();

	if (equipmentInventory == nullptr)
	{
		return;
	}

	const DebugEquipmentSlot validationSlot = this->getDebugSlotForItem(OffsetLabValidationItemKey);
	const std::string currentEquippedItemKey = this->getEquippedItemKey(validationSlot);
	const bool hasValidationItemEquipped = isOffsetLabUnarmedItemKey(OffsetLabValidationItemKey)
		? currentEquippedItemKey.empty()
		: currentEquippedItemKey == OffsetLabValidationItemKey;

	if (!hasValidationItemEquipped)
	{
		equipmentInventory->tryRemove(equipmentInventory->getOffhand(), nullptr, nullptr, false);
		equipmentInventory->tryRemove(equipmentInventory->getHat(), nullptr, nullptr, false);
		equipmentInventory->tryRemove(equipmentInventory->getWeapon(), nullptr, nullptr, false);

		if (!isOffsetLabUnarmedItemKey(OffsetLabValidationItemKey))
		{
			if (Item* item = PlatformerItemDeserializer::getInstance()->createItem(OffsetLabValidationItemKey))
			{
				equipmentInventory->forceInsert(item, false);
			}
		}

		PlatformerEvents::TriggerEquippedItemsChanged();
	}

	this->debugSelectedSlot = validationSlot;
	if (this->debugSelectedSlot != DebugEquipmentSlot::Mainhand && this->debugOffsetTarget == DebugOffsetTarget::WeaponCollision)
	{
		this->debugOffsetTarget = DebugOffsetTarget::Visual;
	}

	appendOffsetLabDebugLine("[OffsetLab][debug] deferred item=" + this->getEquippedItemKey(validationSlot));
	this->syncDebugSelectionToEquipment();
	this->updateEquipmentVisual();
	this->forceAutomationPose(false);

	if (remainingAttempts > 0)
	{
		this->defer([=]()
		{
			this->enforceOffsetLabValidationEquipment(remainingAttempts - 1);
		}, 1);
	}
}

void SquallyEquipmentVisualBehavior::beginOffsetLabAutomation()
{
	if (this->offsetLabAutomationStarted || !GameWindow::isOffsetLabAutomationEnabled() || this->entityInventoryBehavior == nullptr)
	{
		return;
	}

	this->offsetLabAutomationStarted = true;

	EquipmentInventory* equipmentInventory = this->entityInventoryBehavior->getEquipmentInventory();

	if (equipmentInventory == nullptr)
	{
		return;
	}

	const GameWindow::OffsetLabAutomationOptions& options = GameWindow::getOffsetLabAutomationOptions();
	this->debugHud->setVisible(false);
	this->debugSelectedSlot = DebugEquipmentSlot::Mainhand;
	this->debugOffsetsByItem.clear();
	DeveloperModeEvents::TriggerDeveloperModeModeEnable(DeveloperModeEvents::DeveloperModeEnableArgs(1));

	equipmentInventory->tryRemove(equipmentInventory->getOffhand(), nullptr, nullptr, false);
	equipmentInventory->tryRemove(equipmentInventory->getHat(), nullptr, nullptr, false);
	equipmentInventory->tryRemove(equipmentInventory->getWeapon(), nullptr, nullptr, false);

	if (!options.itemKey.empty())
	{
		if (Item* item = PlatformerItemDeserializer::getInstance()->createItem(options.itemKey))
		{
			equipmentInventory->forceInsert(item, false);
		}

		const std::vector<std::string>& catalog = this->getDebugCatalog(DebugEquipmentSlot::Mainhand);
		auto found = std::find(catalog.begin(), catalog.end(), options.itemKey);

		if (found != catalog.end())
		{
			this->debugSelectedWeaponIndex = int(found - catalog.begin());
		}
	}

	PlatformerEvents::TriggerEquippedItemsChanged();
	this->syncDebugSelectionToEquipment();

	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			this->debugCompatibilityLayoutEnabled = true;
			this->updateEquipmentVisual();
			this->forceAutomationPose(false);
		}),
		DelayTime::create(0.10f),
		CallFunc::create([=]() { this->captureOffsetLabAutomationFrame("legacy-compat_right"); }),
		DelayTime::create(0.10f),
		CallFunc::create([=]()
		{
			this->forceAutomationPose(true);
		}),
		DelayTime::create(0.10f),
		CallFunc::create([=]() { this->captureOffsetLabAutomationFrame("legacy-compat_left"); }),
		DelayTime::create(0.10f),
		CallFunc::create([=]()
		{
			this->debugCompatibilityLayoutEnabled = false;
			this->updateEquipmentVisual();
			this->forceAutomationPose(false);
		}),
		DelayTime::create(0.10f),
		CallFunc::create([=]() { this->captureOffsetLabAutomationFrame("direct_right"); }),
		DelayTime::create(0.10f),
		CallFunc::create([=]()
		{
			this->forceAutomationPose(true);
		}),
		DelayTime::create(0.10f),
		CallFunc::create([=]() { this->captureOffsetLabAutomationFrame("direct_left"); }),
		DelayTime::create(0.05f),
		CallFunc::create([=]() { this->finalizeOffsetLabAutomation(); }),
		nullptr
	));
}

void SquallyEquipmentVisualBehavior::captureOffsetLabAutomationFrame(const std::string& captureLabel)
{
	const std::string selectedItemKey = this->getSelectedDebugItemKey();
	const std::string itemKey = selectedItemKey.empty() ? GameWindow::getOffsetLabAutomationOptions().itemKey : selectedItemKey;
	const Vec2 authoredOffset = this->getBaseOffsetForItem(itemKey);
	const Vec2 resolvedOffset = authoredOffset + this->getDebugOffsetForItem(itemKey);
	const std::string facingName = this->squally != nullptr && this->squally->getAnimations() != nullptr && this->squally->getAnimations()->getFlippedX()
		? "left"
		: "right";
	const AnimationPart* mainhandPart = this->squally != nullptr && this->squally->getAnimations() != nullptr
		? this->squally->getAnimations()->getAnimationPart("mainhand")
		: nullptr;
	const Vec2 mainhandWorld = mainhandPart != nullptr ? GameUtils::getWorldCoords(const_cast<AnimationPart*>(mainhandPart), false) : Vec2::ZERO;
	const Vec2 mainhandLocal = mainhandPart != nullptr ? mainhandPart->getPosition() : Vec2::ZERO;
	const Vec2 mainhandScale = mainhandPart != nullptr ? Vec2(mainhandPart->getScaleX(), mainhandPart->getScaleY()) : Vec2::ONE;
	EntityWeaponCollisionBehavior* weaponCollisionBehavior = this->squally == nullptr ? nullptr : this->squally->getComponent<EntityWeaponCollisionBehavior>();
	CollisionObject* mainhandCollision = weaponCollisionBehavior == nullptr ? nullptr : weaponCollisionBehavior->getMainhandWeaponCollision();
	const Vec2 mainhandCollisionWorld = mainhandCollision != nullptr ? GameUtils::getWorldCoords(mainhandCollision, false) : Vec2::ZERO;
	const Vec2 mainhandCollisionLocal = mainhandCollision != nullptr ? mainhandCollision->getPosition() : Vec2::ZERO;
	const std::string outputDirectory = this->getOffsetLabArtifactsDirectory();
	const std::string outputFilePath = outputDirectory + sanitizeArtifactName(itemKey) + "_" + sanitizeArtifactName(captureLabel) + ".bmp";
	const bool saved = this->saveSceneCapture(outputFilePath);

	LogUtils::log("[OffsetLab][automation][" + this->getDebugLayoutName() + "][" + facingName + "] "
		+ itemKey
		+ " authored=" + this->formatVec2(authoredOffset)
		+ " resolved=" + this->formatVec2(resolvedOffset)
		+ " mainhandLocal=" + this->formatVec2(mainhandLocal)
		+ " mainhandWorld=" + this->formatVec2(mainhandWorld)
		+ " mainhandScale=" + this->formatVec2(mainhandScale)
		+ " collisionLocal=" + this->formatVec2(mainhandCollisionLocal)
		+ " collisionWorld=" + this->formatVec2(mainhandCollisionWorld)
		+ " capture=" + outputFilePath
		+ " saved=" + (saved ? "true" : "false"));
}

void SquallyEquipmentVisualBehavior::finalizeOffsetLabAutomation()
{
	const GameWindow::OffsetLabAutomationOptions& options = GameWindow::getOffsetLabAutomationOptions();
	LogUtils::log("[OffsetLab][automation] Artifacts written to " + this->getOffsetLabArtifactsDirectory());

	if (options.quitOnComplete)
	{
		Director::getInstance()->end();
	}
}

void SquallyEquipmentVisualBehavior::forceAutomationPose(bool flippedX)
{
	if (this->squally == nullptr || this->squally->getAnimations() == nullptr)
	{
		return;
	}

	this->squally->getAnimations()->clearAnimationPriority();
	this->squally->getAnimations()->playAnimation("Idle", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(100.0f, 0.0f, true));
	this->squally->getAnimations()->seekAnimationTimeRatio(0.0f);
	this->squally->getAnimations()->setFlippedX(flippedX);
	this->squally->getAnimations()->refreshCurrentAnimationState();
}

bool SquallyEquipmentVisualBehavior::saveSceneCapture(const std::string& outputFilePath) const
{
	Scene* runningScene = Director::getInstance()->getRunningScene();

	if (runningScene == nullptr)
	{
		return false;
	}

	const CSize visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture* renderTexture = RenderTexture::create(int(visibleSize.width), int(visibleSize.height));

	if (renderTexture == nullptr)
	{
		return false;
	}

	renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	runningScene->visit();
	renderTexture->end();
	Director::getInstance()->getRenderer()->render();

	Image* image = renderTexture->newImage(true);
	const bool saved = saveImageAsBmp(image, outputFilePath);

	if (image != nullptr)
	{
		image->release();
	}

	return saved;
}

std::string SquallyEquipmentVisualBehavior::getOffsetLabArtifactsDirectory() const
{
	const std::string outputDirectory = FileUtils::getInstance()->getWritablePath() + "OffsetLab/";
	FileUtils::getInstance()->createDirectory(outputDirectory);
	return outputDirectory;
}

bool SquallyEquipmentVisualBehavior::isOffsetLabValidationMap() const
{
	const std::string ownerMapIdentifier = GameUtils::getKeyOrDefault(this->owner->properties, GameObject::MapKeyMetaMapIdentifier, Value("")).asString();
	const std::string savedMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();
	const std::string savedRespawnMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value("")).asString();

	const std::string targetMap = getOffsetLabValidationMapResource();

	return ownerMapIdentifier == targetMap
		|| savedMap == targetMap
		|| savedRespawnMap == targetMap;
}

void SquallyEquipmentVisualBehavior::initializeDebugKeybindings()
{
	auto bindAltKey = [=](std::set<InputEvents::KeyCode> keys, std::function<void()> callback)
	{
		this->whenKeyPressed(keys, [=](InputEvents::KeyboardEventArgs*)
		{
			if (this->isDebugModifierPressed())
			{
				callback();
			}
		});
	};

	bindAltKey({ InputEvents::KeyCode::KEY_Q }, [=]()
	{
		this->cycleDebugSlot(-1);
	});

	bindAltKey({ InputEvents::KeyCode::KEY_E }, [=]()
	{
		this->cycleDebugSlot(1);
	});

	bindAltKey({ InputEvents::KeyCode::KEY_LEFT_BRACKET }, [=]()
	{
		this->cycleDebugItem(-1);
	});

	bindAltKey({ InputEvents::KeyCode::KEY_RIGHT_BRACKET }, [=]()
	{
		this->cycleDebugItem(1);
	});

	bindAltKey({ InputEvents::KeyCode::KEY_R }, [=]()
	{
		this->resetSelectedDebugOffset();
	});

	bindAltKey({ InputEvents::KeyCode::KEY_P }, [=]()
	{
		if (Input::IsPressed(InputEvents::KeyCode::KEY_SHIFT))
		{
			this->exportAllDebugOffsets();
		}
		else
		{
			this->exportSelectedDebugOffset();
		}
	});

	bindAltKey({ InputEvents::KeyCode::KEY_O }, [=]()
	{
		this->debugHud->setVisible(!this->debugHud->isVisible());
		this->refreshDebugHud();
	});

	bindAltKey({ InputEvents::KeyCode::KEY_C }, [=]()
	{
		this->debugCompatibilityLayoutEnabled = !this->debugCompatibilityLayoutEnabled;
		this->setEquipmentCompatibilityLayoutEnabled(this->debugCompatibilityLayoutEnabled);
		this->updateEquipmentVisual();
	});

	bindAltKey({ InputEvents::KeyCode::KEY_X }, [=]()
	{
		this->toggleDebugOffsetTarget();
	});

	bindAltKey({ InputEvents::KeyCode::KEY_J }, [=]()
	{
		float nudgeAmount = this->isDebugPrecisionModifierPressed() ? SquallyEquipmentVisualBehavior::DebugPrecisionNudgeAmount : SquallyEquipmentVisualBehavior::DebugNudgeAmount;
		this->nudgeSelectedDebugOffset(SquallyEquipmentVisualBehavior::InvertDebugControls ? Vec2(0.0f, -nudgeAmount) : Vec2(-nudgeAmount, 0.0f));
	});

	bindAltKey({ InputEvents::KeyCode::KEY_L }, [=]()
	{
		float nudgeAmount = this->isDebugPrecisionModifierPressed() ? SquallyEquipmentVisualBehavior::DebugPrecisionNudgeAmount : SquallyEquipmentVisualBehavior::DebugNudgeAmount;
		this->nudgeSelectedDebugOffset(SquallyEquipmentVisualBehavior::InvertDebugControls ? Vec2(0.0f, nudgeAmount) : Vec2(nudgeAmount, 0.0f));
	});

	bindAltKey({ InputEvents::KeyCode::KEY_K }, [=]()
	{
		float nudgeAmount = this->isDebugPrecisionModifierPressed() ? SquallyEquipmentVisualBehavior::DebugPrecisionNudgeAmount : SquallyEquipmentVisualBehavior::DebugNudgeAmount;
		this->nudgeSelectedDebugOffset(SquallyEquipmentVisualBehavior::InvertDebugControls ? Vec2(nudgeAmount, 0.0f) : Vec2(0.0f, -nudgeAmount));
	});

	bindAltKey({ InputEvents::KeyCode::KEY_I }, [=]()
	{
		float nudgeAmount = this->isDebugPrecisionModifierPressed() ? SquallyEquipmentVisualBehavior::DebugPrecisionNudgeAmount : SquallyEquipmentVisualBehavior::DebugNudgeAmount;
		this->nudgeSelectedDebugOffset(SquallyEquipmentVisualBehavior::InvertDebugControls ? Vec2(-nudgeAmount, 0.0f) : Vec2(0.0f, nudgeAmount));
	});
}

void SquallyEquipmentVisualBehavior::onDisable()
{
	super::onDisable();
}

void SquallyEquipmentVisualBehavior::refreshDebugHud()
{
	if (!DeveloperModeController::IsDeveloperBuild || this->debugHudStr == nullptr)
	{
		return;
	}

	const std::string selectedItemKey = this->getSelectedDebugItemKey();
	const bool editingWeaponCollision = this->debugOffsetTarget == DebugOffsetTarget::WeaponCollision;
	const cocos2d::Vec2 baseOffset = editingWeaponCollision
		? this->getBaseWeaponCollisionOffsetForItem(selectedItemKey)
		: this->getBaseOffsetForItem(selectedItemKey);
	const cocos2d::Vec2 debugOffset = editingWeaponCollision
		? this->getDebugWeaponCollisionOffsetForItem(selectedItemKey)
		: this->getDebugOffsetForItem(selectedItemKey);
	const cocos2d::Vec2 resolvedOffset = baseOffset + debugOffset;
	const std::vector<std::string>& selectedCatalog = this->getDebugCatalog(this->debugSelectedSlot);
	const int selectedIndex = this->getDebugSelectionIndex(this->debugSelectedSlot);

	std::stringstream stream;
	stream << "Offset Lab\n";
	stream << "Slot: " << this->getDebugSlotName(this->debugSelectedSlot) << "\n";
	stream << "Layout: " << this->getDebugLayoutName() << "\n";
	stream << "Edit: " << this->getDebugOffsetTargetName() << "\n";
	stream << "Item: " << (selectedItemKey.empty() ? "<none>" : selectedItemKey);

	if (!selectedCatalog.empty())
	{
		stream << " (" << selectedIndex + 1 << "/" << selectedCatalog.size() << ")";
	}

	stream << "\n";
	stream << (editingWeaponCollision ? "Collision Authored: " : "Authored: ") << this->formatVec2(baseOffset) << "\n";
	stream << "Adjustment: " << this->formatVec2(debugOffset) << "\n";
	stream << "Resolved: " << this->formatVec2(resolvedOffset) << "\n";

	if (this->isOffsetLabValidationMap())
	{
		stream << "Validation Item: " << OffsetLabValidationItemKey << " (fixed)\n";
		stream << "Controls: Alt+C layout  Alt+X target  Alt+I/J/K/L nudge  Alt+Shift+I/J/K/L fine\n";
		stream << "          Alt+R reset  Alt+P export  Alt+O toggle HUD";
	}
	else
	{
		stream << "Controls: Alt+Q/E slot  Alt+[ / ] item  Alt+C layout  Alt+X target  Alt+I/J/K/L nudge\n";
		stream << "          Alt+Shift+I/J/K/L fine  Alt+R reset  Alt+P export  Alt+Shift+P export touched  Alt+O toggle HUD";
	}

	this->debugHudStr->setString(stream.str());
}

void SquallyEquipmentVisualBehavior::syncDebugSelectionToEquipment()
{
	auto syncSlot = [=](DebugEquipmentSlot slot)
	{
		std::vector<std::string>& catalog = this->getDebugCatalog(slot);
		int& selectedIndex = this->getDebugSelectionIndex(slot);
		const std::string equippedItemKey = this->getEquippedItemKey(slot);

		if (catalog.empty())
		{
			selectedIndex = 0;
			return;
		}

		auto found = std::find(catalog.begin(), catalog.end(), equippedItemKey);

		if (found == catalog.end() && !equippedItemKey.empty())
		{
			catalog.push_back(equippedItemKey);

			if (catalog.size() > 1)
			{
				std::sort(catalog.begin() + 1, catalog.end());
			}

			found = std::find(catalog.begin(), catalog.end(), equippedItemKey);
		}

		selectedIndex = found != catalog.end() ? int(std::distance(catalog.begin(), found)) : 0;
	};

	syncSlot(DebugEquipmentSlot::Mainhand);
	syncSlot(DebugEquipmentSlot::Offhand);
	syncSlot(DebugEquipmentSlot::Hat);
	this->refreshDebugHud();
}

void SquallyEquipmentVisualBehavior::cycleDebugSlot(int direction)
{
	if (this->isOffsetLabValidationMap())
	{
		return;
	}

	const int slotCount = 3;
	int slotIndex = (int)this->debugSelectedSlot;
	slotIndex = (slotIndex + direction + slotCount) % slotCount;
	this->debugSelectedSlot = (DebugEquipmentSlot)slotIndex;

	if (this->debugSelectedSlot != DebugEquipmentSlot::Mainhand && this->debugOffsetTarget == DebugOffsetTarget::WeaponCollision)
	{
		this->debugOffsetTarget = DebugOffsetTarget::Visual;
	}

	this->refreshDebugHud();
}

void SquallyEquipmentVisualBehavior::cycleDebugItem(int direction)
{
	if (this->isOffsetLabValidationMap())
	{
		return;
	}

	std::vector<std::string>& catalog = this->getDebugCatalog(this->debugSelectedSlot);

	if (catalog.empty())
	{
		return;
	}

	int& selectedIndex = this->getDebugSelectionIndex(this->debugSelectedSlot);
	selectedIndex = (selectedIndex + direction + int(catalog.size())) % int(catalog.size());

	this->equipDebugItem(catalog[selectedIndex]);
}

void SquallyEquipmentVisualBehavior::toggleDebugOffsetTarget()
{
	if (this->debugSelectedSlot != DebugEquipmentSlot::Mainhand)
		if (this->debugSelectedSlot == DebugEquipmentSlot::Hat)
		{
			return;
		}

	this->debugOffsetTarget = this->debugOffsetTarget == DebugOffsetTarget::Visual
		? DebugOffsetTarget::WeaponCollision
		: DebugOffsetTarget::Visual;
	this->refreshDebugHud();
}

void SquallyEquipmentVisualBehavior::setEquipmentCompatibilityLayoutEnabled(bool enabled)
{
	if (this->squally == nullptr || this->squally->getAnimations() == nullptr)
	{
		return;
	}

	if (AnimationPart* hat = this->squally->getAnimations()->getAnimationPart("hat"))
	{
		hat->setCompatibilityLayoutEnabled(enabled);
	}

	if (AnimationPart* offhand = this->squally->getAnimations()->getAnimationPart("offhand"))
	{
		offhand->setCompatibilityLayoutEnabled(enabled);
	}

	if (AnimationPart* mainhand = this->squally->getAnimations()->getAnimationPart("mainhand"))
	{
		mainhand->setCompatibilityLayoutEnabled(enabled);
	}
}

void SquallyEquipmentVisualBehavior::nudgeSelectedDebugOffset(const cocos2d::Vec2& delta)
{
	const std::string selectedItemKey = this->getSelectedDebugItemKey();

	if (selectedItemKey.empty())
	{
		return;
	}

	if (this->debugOffsetTarget == DebugOffsetTarget::WeaponCollision)
	{
		if (this->debugSelectedSlot == DebugEquipmentSlot::Hat)
		{
			return;
		}

		this->debugWeaponCollisionOffsetsByItem[selectedItemKey] += delta;
	}
	else
	{
		this->debugOffsetsByItem[selectedItemKey] += delta;
	}

	this->updateEquipmentVisual();
}

void SquallyEquipmentVisualBehavior::resetSelectedDebugOffset()
{
	const std::string selectedItemKey = this->getSelectedDebugItemKey();

	if (selectedItemKey.empty())
	{
		return;
	}

	if (this->debugOffsetTarget == DebugOffsetTarget::WeaponCollision)
	{
		this->debugWeaponCollisionOffsetsByItem.erase(selectedItemKey);
	}
	else
	{
		this->debugOffsetsByItem.erase(selectedItemKey);
	}

	this->updateEquipmentVisual();
}

void SquallyEquipmentVisualBehavior::exportSelectedDebugOffset()
{
	const std::string selectedItemKey = this->getSelectedDebugItemKey();

	if (selectedItemKey.empty())
	{
		return;
	}

	const Vec2 authoredOffset = this->getBaseOffsetForItem(selectedItemKey);
	const Vec2 resolvedOffset = authoredOffset + this->getDebugOffsetForItem(selectedItemKey);
	LogUtils::log("[OffsetLab][" + this->getDebugLayoutName() + "][" + this->getDebugSlotName(this->debugSelectedSlot) + "][visual] " + selectedItemKey + " => " + this->formatVec2(resolvedOffset));

	if (this->debugSelectedSlot != DebugEquipmentSlot::Hat)
	{
		const Vec2 authoredCollisionOffset = this->getBaseWeaponCollisionOffsetForItem(selectedItemKey);
		const Vec2 resolvedCollisionOffset = authoredCollisionOffset + this->getDebugWeaponCollisionOffsetForItem(selectedItemKey);
		LogUtils::log("[OffsetLab][" + this->getDebugLayoutName() + "][" + this->getDebugSlotName(this->debugSelectedSlot) + "][collision] " + selectedItemKey + " => " + this->formatVec2(resolvedCollisionOffset));
	}

	this->refreshDebugHud();
}

void SquallyEquipmentVisualBehavior::exportAllDebugOffsets()
{
	if (this->debugOffsetsByItem.empty() && this->debugWeaponCollisionOffsetsByItem.empty())
	{
		LogUtils::log("[OffsetLab] No offset adjustments recorded.");
		return;
	}

	std::set<std::string> adjustedItemKeys;

	for (const auto& next : this->debugOffsetsByItem)
	{
		adjustedItemKeys.insert(next.first);
	}

	for (const auto& next : this->debugWeaponCollisionOffsetsByItem)
	{
		adjustedItemKeys.insert(next.first);
	}

	LogUtils::log("[OffsetLab] Exporting touched offsets:");

	for (const std::string& itemKey : adjustedItemKeys)
	{
		const Vec2 resolvedOffset = this->getBaseOffsetForItem(itemKey) + this->getDebugOffsetForItem(itemKey);
		LogUtils::log("[OffsetLab][" + this->getDebugLayoutName() + "][visual] " + itemKey + " => " + this->formatVec2(resolvedOffset));

		Item* item = PlatformerItemDeserializer::getInstance()->createItem(itemKey);

		if (dynamic_cast<Weapon*>(item) != nullptr || dynamic_cast<Offhand*>(item) != nullptr)
		{
			const Vec2 resolvedCollisionOffset = this->getBaseWeaponCollisionOffsetForItem(itemKey) + this->getDebugWeaponCollisionOffsetForItem(itemKey);
			LogUtils::log("[OffsetLab][" + this->getDebugLayoutName() + "][collision] " + itemKey + " => " + this->formatVec2(resolvedCollisionOffset));
		}
	}

	this->refreshDebugHud();
}

void SquallyEquipmentVisualBehavior::equipDebugItem(const std::string& itemKey)
{
	if (this->entityInventoryBehavior == nullptr)
	{
		return;
	}

	EquipmentInventory* equipmentInventory = this->entityInventoryBehavior->getEquipmentInventory();

	if (equipmentInventory == nullptr)
	{
		return;
	}

	switch (this->debugSelectedSlot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			equipmentInventory->tryRemove(equipmentInventory->getWeapon(), nullptr, nullptr, false);
			break;
		}
		case DebugEquipmentSlot::Offhand:
		{
			equipmentInventory->tryRemove(equipmentInventory->getOffhand(), nullptr, nullptr, false);
			break;
		}
		case DebugEquipmentSlot::Hat:
		{
			equipmentInventory->tryRemove(equipmentInventory->getHat(), nullptr, nullptr, false);
			break;
		}
	}

	if (!itemKey.empty())
	{
		Item* item = PlatformerItemDeserializer::getInstance()->createItem(itemKey);

		if (item != nullptr)
		{
			equipmentInventory->forceInsert(item, false);
		}
	}

	PlatformerEvents::TriggerEquippedItemsChanged();
}

std::vector<std::string>& SquallyEquipmentVisualBehavior::getDebugCatalog(DebugEquipmentSlot slot)
{
	switch (slot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			return this->debugWeaponKeys;
		}
		case DebugEquipmentSlot::Offhand:
		{
			return this->debugOffhandKeys;
		}
		case DebugEquipmentSlot::Hat:
		{
			return this->debugHatKeys;
		}
	}

	return this->debugWeaponKeys;
}

const std::vector<std::string>& SquallyEquipmentVisualBehavior::getDebugCatalog(DebugEquipmentSlot slot) const
{
	switch (slot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			return this->debugWeaponKeys;
		}
		case DebugEquipmentSlot::Offhand:
		{
			return this->debugOffhandKeys;
		}
		case DebugEquipmentSlot::Hat:
		{
			return this->debugHatKeys;
		}
	}

	return this->debugWeaponKeys;
}

int& SquallyEquipmentVisualBehavior::getDebugSelectionIndex(DebugEquipmentSlot slot)
{
	switch (slot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			return this->debugSelectedWeaponIndex;
		}
		case DebugEquipmentSlot::Offhand:
		{
			return this->debugSelectedOffhandIndex;
		}
		case DebugEquipmentSlot::Hat:
		{
			return this->debugSelectedHatIndex;
		}
	}

	return this->debugSelectedWeaponIndex;
}

int SquallyEquipmentVisualBehavior::getDebugSelectionIndex(DebugEquipmentSlot slot) const
{
	switch (slot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			return this->debugSelectedWeaponIndex;
		}
		case DebugEquipmentSlot::Offhand:
		{
			return this->debugSelectedOffhandIndex;
		}
		case DebugEquipmentSlot::Hat:
		{
			return this->debugSelectedHatIndex;
		}
	}

	return this->debugSelectedWeaponIndex;
}

std::string SquallyEquipmentVisualBehavior::getDebugSlotName(DebugEquipmentSlot slot) const
{
	switch (slot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			return "mainhand";
		}
		case DebugEquipmentSlot::Offhand:
		{
			return "offhand";
		}
		case DebugEquipmentSlot::Hat:
		{
			return "hat";
		}
	}

	return "mainhand";
}

std::string SquallyEquipmentVisualBehavior::getDebugOffsetTargetName() const
{
	switch (this->debugOffsetTarget)
	{
		case DebugOffsetTarget::Visual:
		{
			return "visual";
		}
		case DebugOffsetTarget::WeaponCollision:
		{
			return "hitbox";
		}
	}

	return "visual";
}

SquallyEquipmentVisualBehavior::DebugEquipmentSlot SquallyEquipmentVisualBehavior::getDebugSlotForItem(const std::string& itemKey) const
{
	Item* item = itemKey.empty() ? nullptr : PlatformerItemDeserializer::getInstance()->createItem(itemKey);

	if (dynamic_cast<Hat*>(item) != nullptr)
	{
		return DebugEquipmentSlot::Hat;
	}

	if (dynamic_cast<Offhand*>(item) != nullptr)
	{
		return DebugEquipmentSlot::Offhand;
	}

	return DebugEquipmentSlot::Mainhand;
}

std::string SquallyEquipmentVisualBehavior::getEquippedItemKey(DebugEquipmentSlot slot) const
{
	if (this->entityInventoryBehavior == nullptr || this->entityInventoryBehavior->getEquipmentInventory() == nullptr)
	{
		return "";
	}

	switch (slot)
	{
		case DebugEquipmentSlot::Mainhand:
		{
			Weapon* weapon = this->entityInventoryBehavior->getEquipmentInventory()->getWeapon();
			return weapon == nullptr ? "" : weapon->getIdentifier();
		}
		case DebugEquipmentSlot::Offhand:
		{
			Offhand* offhand = this->entityInventoryBehavior->getEquipmentInventory()->getOffhand();
			return offhand == nullptr ? "" : offhand->getIdentifier();
		}
		case DebugEquipmentSlot::Hat:
		{
			Hat* hat = this->entityInventoryBehavior->getEquipmentInventory()->getHat();
			return hat == nullptr ? "" : hat->getIdentifier();
		}
	}

	return "";
}

std::string SquallyEquipmentVisualBehavior::getSelectedDebugItemKey() const
{
	if (this->isOffsetLabValidationMap() && this->debugSelectedSlot == DebugEquipmentSlot::Mainhand && isOffsetLabUnarmedItemKey(OffsetLabValidationItemKey))
	{
		return OffsetLabValidationItemKey;
	}

	const std::vector<std::string>& catalog = this->getDebugCatalog(this->debugSelectedSlot);

	if (catalog.empty())
	{
		return "";
	}

	const int selectedIndex = this->getDebugSelectionIndex(this->debugSelectedSlot);

	if (selectedIndex < 0 || selectedIndex >= int(catalog.size()))
	{
		return "";
	}

	return catalog[selectedIndex];
}

cocos2d::Vec2 SquallyEquipmentVisualBehavior::getDebugOffsetForItem(const std::string& itemKey) const
{
	auto found = this->debugOffsetsByItem.find(itemKey);
	return found != this->debugOffsetsByItem.end() ? found->second : Vec2::ZERO;
}

cocos2d::Vec2 SquallyEquipmentVisualBehavior::getDebugWeaponCollisionOffsetForItem(const std::string& itemKey) const
{
	auto found = this->debugWeaponCollisionOffsetsByItem.find(itemKey);
	return found != this->debugWeaponCollisionOffsetsByItem.end() ? found->second : Vec2::ZERO;
}

std::string SquallyEquipmentVisualBehavior::getDebugLayoutName() const
{
	return this->debugCompatibilityLayoutEnabled ? "legacy-compat" : "direct";
}

cocos2d::Vec2 SquallyEquipmentVisualBehavior::getBaseOffsetForItem(const std::string& itemKey) const
{
	if (itemKey.empty())
	{
		return Vec2::ZERO;
	}

	if (isOffsetLabUnarmedItemKey(itemKey))
	{
		return Vec2::ZERO;
	}

	Item* item = PlatformerItemDeserializer::getInstance()->createItem(itemKey);
	Equipable* equipable = dynamic_cast<Equipable*>(item);

	return equipable == nullptr ? Vec2::ZERO : equipable->getDisplayOffset();
}

cocos2d::Vec2 SquallyEquipmentVisualBehavior::getBaseWeaponCollisionOffsetForItem(const std::string& itemKey) const
{
	if (itemKey.empty())
	{
		return Vec2::ZERO;
	}

	if (isOffsetLabUnarmedItemKey(itemKey))
	{
		return OffsetLabUnarmedCollisionOffset;
	}

	Item* item = PlatformerItemDeserializer::getInstance()->createItem(itemKey);
	Weapon* weapon = dynamic_cast<Weapon*>(item);
	Offhand* offhand = dynamic_cast<Offhand*>(item);

	if (weapon != nullptr)
	{
		return weapon->getWeaponCollisionOffset();
	}

	return offhand == nullptr ? Vec2::ZERO : offhand->getOffhandOffset();
}

bool SquallyEquipmentVisualBehavior::isDebugModifierPressed() const
{
	return Input::IsPressed(InputEvents::KeyCode::KEY_ALT);
}

bool SquallyEquipmentVisualBehavior::isDebugPrecisionModifierPressed() const
{
	return Input::IsPressed(InputEvents::KeyCode::KEY_SHIFT);
}

std::string SquallyEquipmentVisualBehavior::formatVec2(const cocos2d::Vec2& value) const
{
	std::stringstream stream;
	stream << "Vec2(" << std::fixed << std::setprecision(2) << value.x << "f, " << value.y << "f)";
	return stream.str();
}

void SquallyEquipmentVisualBehavior::updateEquipmentVisual()
{
	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->setEquipmentCompatibilityLayoutEnabled(this->debugCompatibilityLayoutEnabled);
		this->refreshDebugHud();
	}

	if (this->entityInventoryBehavior == nullptr || this->entityInventoryBehavior->getEquipmentInventory() == nullptr)
	{
		return;
	}

	EquipmentInventory* equipmentInventory = this->entityInventoryBehavior->getEquipmentInventory();
	Weapon* weapon = equipmentInventory->getWeapon();
	Hat* hat = equipmentInventory->getHat();
	Offhand* offhand = equipmentInventory->getOffhand();

	AnimationPart* hatAnim = this->squally->getAnimations()->getAnimationPart("hat");
	if (hatAnim != nullptr)
	{
		if (hat != nullptr)
		{
			hatAnim->replaceSprite(hat->getIconResource());
			hatAnim->setOffset(hat->getDisplayOffset() + this->getDebugOffsetForItem(hat->getIdentifier()));
		}
		else
		{
			hatAnim->restoreSprite();
			hatAnim->restoreOffset();
		}
	}

	AnimationPart* offhandAnim = this->squally->getAnimations()->getAnimationPart("offhand");
	if (offhandAnim != nullptr)
	{
		if (offhand != nullptr)
		{
			offhandAnim->replaceSprite(offhand->getIconResource());
			offhandAnim->setOffset(offhand->getDisplayOffset() + this->getDebugOffsetForItem(offhand->getIdentifier()));
		}
		else
		{
			offhandAnim->restoreSprite();
			offhandAnim->restoreOffset();
		}
	}

	AnimationPart* mainhand = this->squally->getAnimations()->getAnimationPart("mainhand");
	if (mainhand != nullptr)
	{
		if (this->isOffsetLabValidationMap())
		{
			appendOffsetLabDebugLine("[OffsetLab][debug] update visual weapon=" + std::string(weapon == nullptr ? "<none>" : weapon->getIdentifier()));
		}

		if (weapon != nullptr)
		{
			mainhand->replaceSprite(weapon->getIconResource());
			mainhand->setOffset(weapon->getDisplayOffset() + this->getDebugOffsetForItem(weapon->getIdentifier()));
		}
		else
		{
			mainhand->restoreSprite();
			mainhand->restoreOffset();
		}
	}

	EntityWeaponCollisionBehavior* weaponCollisionBehavior = this->squally->getComponent<EntityWeaponCollisionBehavior>();

	if (weaponCollisionBehavior != nullptr)
	{
		const Vec2 debugWeaponCollisionOffset = weapon != nullptr
			? this->getDebugWeaponCollisionOffsetForItem(weapon->getIdentifier())
			: (this->isOffsetLabValidationMap() && isOffsetLabUnarmedItemKey(OffsetLabValidationItemKey)
				? this->getDebugWeaponCollisionOffsetForItem(OffsetLabValidationItemKey)
				: Vec2::ZERO);
		const Vec2 debugOffhandCollisionOffset = offhand == nullptr
			? Vec2::ZERO
			: this->getDebugWeaponCollisionOffsetForItem(offhand->getIdentifier());

		weaponCollisionBehavior->setWeaponCollisionDebugOffset(debugWeaponCollisionOffset);
		weaponCollisionBehavior->setOffhandWeaponCollisionDebugOffset(debugOffhandCollisionOffset);
	}
}
