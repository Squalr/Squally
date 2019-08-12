#include "SquallyOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyOutOfCombatAttackBehavior::MapKeyAttachedBehavior = "squally-attack";

SquallyOutOfCombatAttackBehavior* SquallyOutOfCombatAttackBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyOutOfCombatAttackBehavior* instance = new SquallyOutOfCombatAttackBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyOutOfCombatAttackBehavior::SquallyOutOfCombatAttackBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyOutOfCombatAttackBehavior::~SquallyOutOfCombatAttackBehavior()
{
}

void SquallyOutOfCombatAttackBehavior::onLoad()
{
	this->scheduleUpdate();

	this->squally->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		this->doOutOfCombatAttack(this->getOutOfCombatAttackAnimation(), this->getOutOfCombatAttackOnset(), this->getOutOfCombatAttackSustain());
	});
}

std::string SquallyOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
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

float SquallyOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
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

float SquallyOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
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
