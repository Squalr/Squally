#include "Squally.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/IsAliveClippy.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Entities/Squally/IsAlive/IsAlive.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_IS_ALIVE 1

const std::string Squally::EventSquallyTrapped = "event-squally-trapped";

const float Squally::SquallyScale = 0.92f;
const std::string Squally::MapKeySqually = "squally";
const std::string Squally::IdentifierIsAlive = "is-alive";
const int Squally::SquallyBaseHealth = 16;
const int Squally::SquallyBaseSpecial = 8;

Squally* Squally::deserialize(ValueMap& properties)
{
	Squally* instance = new Squally(properties);

	instance->autorelease();
	
	return instance;
}

Squally::Squally(ValueMap& properties) : super(properties,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	PlatformerCollisionType::Player,
	Size(128.0f, 128.0f),
	Squally::SquallyScale,
	Vec2(0.0f, 24.0f),
	Squally::SquallyBaseHealth,
	Squally::SquallyBaseSpecial,
	Size(128.0f, 224.0f),
	24.0f,
	PlatformerCollisionType::PlayerMovement,
	SaveKeys::SaveKeySquallyInventory,
	SaveKeys::SaveKeySquallyEquipment,
	SaveKeys::SaveKeySquallyCurrencyInventory)
{
	this->cameraTrackTarget = Node::create();
	this->leftEyeController = SmartAnimationSequenceNode::create();
	this->rightEyeController = SmartAnimationSequenceNode::create();

	this->registerHackables();
	this->registerAttack(Punch::create(0.4f, 0.5f));

	this->leftEyeController->setVisible(false);
	this->rightEyeController->setVisible(false);

	this->addChild(this->cameraTrackTarget);
	this->addChild(this->leftEyeController);
	this->addChild(this->rightEyeController);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	this->loadState();
	this->runEyeBlinkLoop();

	// Request camera track player
	CameraTrackingData trackingData = CameraTrackingData(this->cameraTrackTarget, Vec2(128.0f, 96.0f));
	GameCamera::getInstance()->setTarget(trackingData, true);
}

void Squally::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Request HUD track player
	PlatformerEvents::TriggerHudTrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
}

void Squally::initializePositions()
{
	super::initializePositions();

	this->cameraTrackTarget->setPosition(Vec2(0.0f, 128.0f));
}

void Squally::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::TriggerHudUntrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
		this->saveState();
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToLocation, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::WarpArgs* args = static_cast<PlatformerEvents::WarpArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->setPosition(args->position);
			GameCamera::getInstance()->setCameraPositionToTrackedTarget();
		}
	}));

	this->addEventListener(EventListenerCustom::create(HackableEvents::EventForceHackerModeEnable, [=](EventCustom*)
	{
		this->tryUseRune();
		
		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getEq()));
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_TAB }, [=](InputEvents::InputArgs* args)
	{
		args->handle();
		
		if (this->tryUseRune())
		{
			HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getEq()));
		}
	});

	this->whenKeyPressedHackerMode({ EventKeyboard::KeyCode::KEY_TAB, EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		args->handle();

		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getEq()));
	});

	this->listenForMapEvent(Squally::EventSquallyTrapped, [=](ValueMap args)
	{
		for (auto it = this->codeList.begin(); it != this->codeList.end(); it++)
		{
			if ((*it)->getHackableCodeIdentifier() == Squally::IdentifierIsAlive)
			{
				(*it)->getClippy()->setIsEnabled(true);
			}
		}
	});
}

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

float Squally::getFloatHeight()
{
	return 64.0f;
}

cocos2d::Vec2 Squally::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Squally::performSwimAnimation()
{
	if (this->equipmentInventory->getWeapon() != nullptr)
	{
		this->animationNode->playAnimation("SwimWithWeapon");
	}
	else
	{
		this->animationNode->playAnimation("Swim");
	}
}

void Squally::onHackerModeEnable(int eq)
{
	super::onHackerModeEnable(eq);
}

void Squally::registerHackables()
{
	super::registerHackables();

	IsAliveClippy* isAliveClippy = IsAliveClippy::create();

	isAliveClippy->setIsEnabled(true);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_IS_ALIVE,
			HackableCode::LateBindData(
				Squally::IdentifierIsAlive,
				Strings::Hacking_Entities_Squally_IsAlive_IsAlive::create(),
				UIResources::Menus_Icons_Heart,
				EntityPreview::create(this),
				{
				},
				2,
				1.0f,
				isAliveClippy
			)
		},
	};

	auto isAliveSquallyFunc = &Squally::isAliveSqually;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)isAliveSquallyFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

NO_OPTIMIZE bool Squally::isAliveSqually()
{
	static volatile int isAlive = true;

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_IS_ALIVE);

	ASM(mov ZAX, 1);

	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(isAlive, ZAX);

	HACKABLES_STOP_SEARCH();

	return isAlive;
}

void Squally::saveState()
{
	ValueVector cooldowns = ValueVector();

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		cooldowns.push_back(Value(this->getRuneCooldown(index)));
	}

	SaveManager::batchSaveProfileData({
		{ SaveKeys::SaveKeySquallyHeath, Value(this->getHealth()) },
		{ SaveKeys::SaveKeySquallyMana, Value(this->getMana()) },
		{ SaveKeys::SaveKeySquallyRuneCooldowns, Value(cooldowns) },
		{ SaveKeys::SaveKeySquallyEqExperience, Value(this->getEqExperience()) },
		{ SaveKeys::SaveKeySquallyEq, Value(this->getEq()) }
	});
}

void Squally::loadState()
{
	// Note: We just use the current value by default. This is normally the max if Squally was just constructed, but might also
	// Be a lower value (ie if created as injured for a cutscene)
	this->setHealth(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHeath, Value(this->getHealth())).asInt());
	this->setMana(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(this->getMana())).asInt());
	this->setEq(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEq, Value(Squally::DefaultEq)).asInt());
	this->setEqExperience(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEqExperience, Value(this->getEqExperience())).asInt());

	ValueVector cooldowns = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyRuneCooldowns, Value(ValueVector())).asValueVector();

	for (int index = 0; index < std::min((int)cooldowns.size(), (int)this->getMaxRunes()); index++)
	{
		this->setRuneCooldown(index, cooldowns[index].asFloat());
	}
	
	this->setPosition(Vec2(
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(this->getPositionX())).asFloat(),
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(this->getPositionY())).asFloat()
	));

	if (this->getHealth() <= 0)
	{
		this->killAndRespawn();
	}

	// Save new defaults
	this->saveState();
}

void Squally::runEyeBlinkLoop()
{
	const float BlinkSpeed = 0.0075f;
	const float EyesClosedDuration = 0.015f;
	const float TimeBetweenBlinks = 5.5f;
	
	this->leftEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->leftEyeController->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* leftEye = this->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->leftEyeController->getBackwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* leftEye = this->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->rightEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->rightEyeController->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* rightEye = this->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->rightEyeController->getBackwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* rightEye = this->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
}
