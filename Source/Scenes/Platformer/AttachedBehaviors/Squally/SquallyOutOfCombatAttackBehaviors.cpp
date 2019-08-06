#include "SquallyOutOfCombatAttackBehaviors.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyOutOfCombatAttackBehaviors::MapKeyAttachedBehavior = "squally-attack";

SquallyOutOfCombatAttackBehaviors* SquallyOutOfCombatAttackBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyOutOfCombatAttackBehaviors* instance = new SquallyOutOfCombatAttackBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyOutOfCombatAttackBehaviors::SquallyOutOfCombatAttackBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyOutOfCombatAttackBehaviors::~SquallyOutOfCombatAttackBehaviors()
{
}

void SquallyOutOfCombatAttackBehaviors::onLoad()
{
	this->scheduleUpdate();

	this->squally->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		this->doOutOfCombatAttack(this->getOutOfCombatAttackAnimation(), this->getOutOfCombatAttackOnset(), this->getOutOfCombatAttackSustain());
	});
}

std::string SquallyOutOfCombatAttackBehaviors::getOutOfCombatAttackAnimation()
{
	Weapon* weapon = this->squally->equipmentInventory->getWeapon();

	if (weapon != nullptr)
	{
		return "AttackFast";
	}
	else
	{
		return "AttackPunchFast";
	}
}

float SquallyOutOfCombatAttackBehaviors::getOutOfCombatAttackOnset()
{
	Weapon* weapon = this->squally->equipmentInventory->getWeapon();

	if (weapon == nullptr)
	{
		return 0.2f;
	}
	else
	{
		return weapon->getAttackOnset();
	}
}

float SquallyOutOfCombatAttackBehaviors::getOutOfCombatAttackSustain()
{
	Weapon* weapon = this->squally->equipmentInventory->getWeapon();

	if (weapon == nullptr)
	{
		return 0.15f;
	}
	else
	{
		return weapon->getAttackSustain();
	}
}
