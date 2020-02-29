#include "SquallyEquipmentVisualBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyEquipmentVisualBehavior::MapKeyAttachedBehavior = "squally-equipment-visuals";

SquallyEquipmentVisualBehavior* SquallyEquipmentVisualBehavior::create(GameObject* owner)
{
	SquallyEquipmentVisualBehavior* instance = new SquallyEquipmentVisualBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyEquipmentVisualBehavior::SquallyEquipmentVisualBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->debugOffset = Vec2::ZERO;
	this->debugHud = Node::create();
	this->debugOffsetXStr = ConstantString::create("--");
	this->debugOffsetYStr = ConstantString::create("--");
	this->debugOffsetXLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->debugOffsetXStr);
	this->debugOffsetYLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->debugOffsetYStr);
	
	this->debugHud->setVisible(false);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->debugHud->addChild(this->debugOffsetXLabel);
	this->debugHud->addChild(this->debugOffsetYLabel);
	this->addChild(this->debugHud);
}

SquallyEquipmentVisualBehavior::~SquallyEquipmentVisualBehavior()
{
}

void SquallyEquipmentVisualBehavior::initializePositions()
{
	super::initializePositions();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->debugOffsetXLabel->setPosition(Vec2(96.0f, 48.0f + 32.0f));
	this->debugOffsetYLabel->setPosition(Vec2(96.0f, 48.0f));
}

void SquallyEquipmentVisualBehavior::onLoad()
{
	this->updateEquipmentVisual();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->debugOffset = Vec2::ZERO;
		this->updateEquipmentVisual();
	}));

	if (DeveloperModeController::IsDeveloperBuild)
	{
		this->debugHud->setVisible(true);

		this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_J }, [=](InputEvents::InputArgs* args)
		{
			if (Input::isPressed(EventKeyboard::KeyCode::KEY_ALT))
			{
				this->debugOffset.x -= 2.0f;
				this->updateEquipmentVisual();
			}
		});

		this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_L }, [=](InputEvents::InputArgs* args)
		{
			if (Input::isPressed(EventKeyboard::KeyCode::KEY_ALT))
			{
				this->debugOffset.x += 2.0f;
				this->updateEquipmentVisual();
			}
		});

		this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_K }, [=](InputEvents::InputArgs* args)
		{
			if (Input::isPressed(EventKeyboard::KeyCode::KEY_ALT))
			{
				this->debugOffset.y -= 2.0f;
				this->updateEquipmentVisual();
			}
		});

		this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_I }, [=](InputEvents::InputArgs* args)
		{
			if (Input::isPressed(EventKeyboard::KeyCode::KEY_ALT))
			{
				this->debugOffset.y += 2.0f;
				this->updateEquipmentVisual();
			}
		});
	}
}

void SquallyEquipmentVisualBehavior::updateEquipmentVisual()
{
	if (DeveloperModeController::IsDeveloperBuild)
	{
		std::stringstream streamX = std::stringstream();
		std::stringstream streamY = std::stringstream();
		std::stringstream streamZoom = std::stringstream();

		streamX << std::fixed << std::setprecision(2) << this->debugOffset.x;
		streamY << std::fixed << std::setprecision(2) << this->debugOffset.y;

		this->debugOffsetXStr->setString(streamX.str());
		this->debugOffsetYStr->setString(streamY.str());
	}

	this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Weapon* weapon = entityInventoryBehavior->getEquipmentInventory()->getWeapon();
		Hat* hat = entityInventoryBehavior->getEquipmentInventory()->getHat();
		Offhand* offhand = entityInventoryBehavior->getEquipmentInventory()->getOffhand();
		AnimationPart* hatAnim = this->squally->getAnimations()->getAnimationPart("hat");
		
		if (hatAnim != nullptr)
		{
			if (hat != nullptr)
			{
				hatAnim->replaceSprite(hat->getIconResource());
				hatAnim->setOffset(hat->getDisplayOffset() + this->debugOffset);
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
				offhandAnim->setOffset(offhand->getDisplayOffset());
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
			if (weapon != nullptr)
			{
				mainhand->replaceSprite(weapon->getIconResource());
				mainhand->setOffset(weapon->getDisplayOffset());
			}
			else
			{
				mainhand->restoreSprite();
				mainhand->restoreOffset();
			}
		}
	});
}
