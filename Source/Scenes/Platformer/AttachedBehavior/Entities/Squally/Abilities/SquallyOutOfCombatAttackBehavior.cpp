#include "SquallyOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Arrows/CrystalArrow.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string SquallyOutOfCombatAttackBehavior::MapKey = "squally-attack";

SquallyOutOfCombatAttackBehavior* SquallyOutOfCombatAttackBehavior::create(GameObject* owner)
{
	SquallyOutOfCombatAttackBehavior* instance = new SquallyOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyOutOfCombatAttackBehavior::SquallyOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->projectile = nullptr;

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
		this->doOutOfCombatAttack(this->getOutOfCombatAttackAnimation(), this->getOutOfCombatAttackSound(), this->getOutOfCombatAttackOnset(), this->getOutOfCombatAttackSustain());
	});
}

void SquallyOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

std::string SquallyOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	Weapon* weapon = this->getWeapon();

	if (weapon == nullptr)
	{
		return "AttackOverworldPunch";
	}
	else if (dynamic_cast<Bow*>(weapon) != nullptr)
	{
		return "AttackOverworldShoot";
	}
	else
	{
		return "AttackOverworldSlash";
	}
}

std::string SquallyOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	Weapon* weapon = this->getWeapon();

	if (weapon == nullptr)
	{
		return SoundResources::Platformer_Combat_Attacks_Physical_Punches_PunchWoosh1;
	}
	else
	{
		return weapon->getWeaponAttackSound();
	}
}

float SquallyOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	Weapon* weapon = this->getWeapon();

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
	Weapon* weapon = this->getWeapon();

	if (weapon == nullptr)
	{
		return 0.15f;
	}
	else
	{
		return weapon->getAttackSustain();
	}
}

Weapon* SquallyOutOfCombatAttackBehavior::getWeapon()
{
	Weapon* weapon = nullptr;

	this->squally->getAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
	{
		weapon = entityInventoryBehavior->getEquipmentInventory()->getWeapon();
	});

	return weapon;
}

Projectile* SquallyOutOfCombatAttackBehavior::createProjectile()
{
	Weapon* weapon = this->getWeapon();

	if (weapon == nullptr)
	{
		return nullptr;
	}
	
	if (dynamic_cast<CrystalBow*>(weapon) != nullptr)
	{
		return dynamic_cast<CrystalArrow*>(this->cachedProjectile) != nullptr ? this->cachedProjectile : this->createProjectile([](){ return CrystalArrow::create(); });
	}

	return nullptr;
}

Projectile* SquallyOutOfCombatAttackBehavior::createProjectile(std::function<Projectile*()> createFunc)
{
	Projectile* projectile = createFunc();

	projectile->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionObject::CollisionData collisionData)
	{
		if (!this->squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		PlatformerEnemy* enemy = GameUtils::getFirstParentOfType<PlatformerEnemy>(collisionData.other);

		if (enemy != nullptr && enemy->getStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			// Encountered enemy w/ first-strike
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, true));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	return projectile;
}
