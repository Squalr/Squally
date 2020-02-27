#include "SquallyAttackBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/Axe.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Spears/Spear.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Sword/Slash.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string SquallyAttackBehavior::MapKeyAttachedBehavior = "squally-attacks";

SquallyAttackBehavior* SquallyAttackBehavior::create(GameObject* owner)
{
	SquallyAttackBehavior* instance = new SquallyAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyAttackBehavior::SquallyAttackBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyAttackBehavior::~SquallyAttackBehavior()
{
}

void SquallyAttackBehavior::initializePositions()
{
}

void SquallyAttackBehavior::onLoad()
{
	this->squally->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{

		this->loadWeaponAttacks(attackBehavior);
	});
}

void SquallyAttackBehavior::loadWeaponAttacks(EntityAttackBehavior* attackBehavior)
{
	this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* inventoryBehavior)
	{
		Weapon* weapon = inventoryBehavior->getEquipmentInventory()->getWeapon();

		if (static_cast<Axe*>(weapon) != nullptr)
		{
			this->loadAxeAttacks(attackBehavior, inventoryBehavior, static_cast<Axe*>(weapon));
		}
		else if (static_cast<Bow*>(weapon) != nullptr)
		{
			this->loadBowAttacks(attackBehavior, inventoryBehavior, static_cast<Bow*>(weapon));
		}
		else if (static_cast<Mace*>(weapon) != nullptr)
		{
			this->loadMaceAttacks(attackBehavior, inventoryBehavior, static_cast<Mace*>(weapon));
		}
		else if (static_cast<Spear*>(weapon) != nullptr)
		{
			this->loadSpearAttacks(attackBehavior, inventoryBehavior, static_cast<Spear*>(weapon));
		}
		else if (static_cast<Sword*>(weapon) != nullptr)
		{
			this->loadSwordAttacks(attackBehavior, inventoryBehavior, static_cast<Sword*>(weapon));
		}
		else if (static_cast<Wand*>(weapon) != nullptr)
		{
			this->loadWandAttacks(attackBehavior, inventoryBehavior, static_cast<Wand*>(weapon));
		}
		else
		{
			this->loadUnarmedAttacks(attackBehavior);
		}
	});
}

void SquallyAttackBehavior::loadUnarmedAttacks(EntityAttackBehavior* attackBehavior)
{
	attackBehavior->registerAttack(Punch::create(0.4f, EntityAttackBehavior::DefaultRecoverSpeed));
}

void SquallyAttackBehavior::loadAxeAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Axe* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword, inventoryBehavior);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(Slash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
}

void SquallyAttackBehavior::loadBowAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Bow* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword, inventoryBehavior);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(Slash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
}

void SquallyAttackBehavior::loadMaceAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Mace* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword, inventoryBehavior);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(Slash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
}

void SquallyAttackBehavior::loadSpearAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Spear* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword, inventoryBehavior);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(Slash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
}

void SquallyAttackBehavior::loadSwordAttacks(EntityAttackBehavior* attackBehavior, EntityInventoryBehavior* inventoryBehavior, Sword* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword, inventoryBehavior);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(Slash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
}

void SquallyAttackBehavior::loadWandAttacks(EntityAttackBehavior* attackBehavior,EntityInventoryBehavior* inventoryBehavior, Wand* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword, inventoryBehavior);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(Slash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
}

std::tuple<int, int> SquallyAttackBehavior::computeWeaponDamageRange(Weapon* weapon, EntityInventoryBehavior* inventoryBehavior)
{
	int minAttack = 0;
	int maxAttack = 0;

	if (weapon != nullptr)
	{
		minAttack += weapon->getMinAttack();
		maxAttack += weapon->getMaxAttack();
	}

	for (auto next : inventoryBehavior->getEquipmentInventory()->getEquipment())
	{
		minAttack += next->getItemStats().attackBonus;
		maxAttack += next->getItemStats().attackBonus;
	}

	return std::make_tuple(minAttack, maxAttack);
}
