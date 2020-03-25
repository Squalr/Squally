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
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttacks.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string SquallyAttackBehavior::MapKey = "squally-attacks";

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

void SquallyAttackBehavior::onDisable()
{
	super::onDisable();
}

void SquallyAttackBehavior::loadWeaponAttacks(EntityAttackBehavior* attackBehavior)
{
	attackBehavior->registerAttack(CastHaste::create(0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));

	this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* inventoryBehavior)
	{
		Weapon* weapon = inventoryBehavior->getEquipmentInventory()->getWeapon();

		if (dynamic_cast<Axe*>(weapon) != nullptr)
		{
			this->loadAxeAttacks(attackBehavior, dynamic_cast<Axe*>(weapon));
		}
		else if (dynamic_cast<Bow*>(weapon) != nullptr)
		{
			this->loadBowAttacks(attackBehavior, dynamic_cast<Bow*>(weapon));
		}
		else if (dynamic_cast<Mace*>(weapon) != nullptr)
		{
			this->loadMaceAttacks(attackBehavior, dynamic_cast<Mace*>(weapon));
		}
		else if (dynamic_cast<Sword*>(weapon) != nullptr)
		{
			this->loadSwordAttacks(attackBehavior, dynamic_cast<Sword*>(weapon));
		}
		else if (dynamic_cast<Wand*>(weapon) != nullptr)
		{
			this->loadWandAttacks(attackBehavior, dynamic_cast<Wand*>(weapon));
		}
		else
		{
			this->loadUnarmedAttacks(attackBehavior);
		}
	});
}

void SquallyAttackBehavior::loadUnarmedAttacks(EntityAttackBehavior* attackBehavior)
{
	attackBehavior->registerAttack(Punch::create(0.4f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
}

void SquallyAttackBehavior::loadAxeAttacks(EntityAttackBehavior* attackBehavior, Axe* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(AxeSwing::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
}

void SquallyAttackBehavior::loadBowAttacks(EntityAttackBehavior* attackBehavior, Bow* bow)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(bow);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(BowShoot::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
}

void SquallyAttackBehavior::loadMaceAttacks(EntityAttackBehavior* attackBehavior, Mace* mace)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(mace);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(MaceSwing::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
}

void SquallyAttackBehavior::loadSwordAttacks(EntityAttackBehavior* attackBehavior, Sword* sword)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(sword);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(SwordSlash::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	attackBehavior->registerAttack(SwordExecute::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
}

void SquallyAttackBehavior::loadWandAttacks(EntityAttackBehavior* attackBehavior, Wand* wand)
{
	std::tuple<int, int> attackRange = this->computeWeaponDamageRange(wand);
	int minAttack = std::get<0>(attackRange);
	int maxAttack = std::get<1>(attackRange);

	attackBehavior->registerAttack(WandSwing::create(minAttack, maxAttack, 0.35f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
}

std::tuple<int, int> SquallyAttackBehavior::computeWeaponDamageRange(Weapon* weapon)
{
	int minAttack = 0;
	int maxAttack = 0;

	if (weapon != nullptr)
	{
		minAttack += weapon->getMinAttack();
		maxAttack += weapon->getMaxAttack();
	}

	return std::make_tuple(minAttack, maxAttack);
}
