#include "SquallyEquipmentVisualBehaviors.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyEquipmentVisualBehaviors::MapKeyAttachedBehavior = "squally-equipment-visuals";

SquallyEquipmentVisualBehaviors* SquallyEquipmentVisualBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyEquipmentVisualBehaviors* instance = new SquallyEquipmentVisualBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyEquipmentVisualBehaviors::SquallyEquipmentVisualBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyEquipmentVisualBehaviors::~SquallyEquipmentVisualBehaviors()
{
}

void SquallyEquipmentVisualBehaviors::onLoad()
{
	this->updateEquipmentVisual();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->updateEquipmentVisual();
	}));
}

void SquallyEquipmentVisualBehaviors::updateEquipmentVisual()
{
	Weapon* weapon = this->squally->equipmentInventory->getWeapon();
	Hat* hat = this->squally->equipmentInventory->getHat();
	Offhand* offhand = this->squally->equipmentInventory->getOffhand();

	AnimationPart* hatAnim = this->squally->getAnimations()->getAnimationPart("hat");
	
	if (hatAnim != nullptr)
	{
		if (hat != nullptr)
		{
			hatAnim->replaceSprite(hat->getIconResource());
			hatAnim->setOffset(hat->getDisplayOffset());
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

	if (weapon != nullptr)
	{
		this->squally->rebuildWeaponCollision(weapon->getWeaponCollisionSize());
		this->squally->weaponCollision->setPosition(weapon->getWeaponOffset());
	}
	else
	{
		const Size NoWeaponSize = Size(64.0f, 64.0f);
		const Vec2 NoWeaponOffset = Vec2(0.0f, 96.0f);

		this->squally->rebuildWeaponCollision(NoWeaponSize);
		this->squally->weaponCollision->setPosition(NoWeaponOffset);
	}
}
