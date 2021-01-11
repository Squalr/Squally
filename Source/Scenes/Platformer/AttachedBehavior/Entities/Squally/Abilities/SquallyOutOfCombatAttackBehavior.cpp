#include "SquallyOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Projectiles/Arrows/BoneArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/CrystalArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/DemonicArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/GoldenArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/HuntersArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/IvyArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/SteelArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/VoidArrow.h"
#include "Objects/Platformer/Projectiles/Arrows/WoodenArrow.h"
#include "Objects/Platformer/Projectiles/WandSpells/EnergyBolt.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"
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
	super::onLoad();

	this->squally->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->attack();
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
		return SoundResources::Platformer_Physical_Punches_PunchWoosh1;
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

	Projectile* projectile = nullptr;

	// Bows
	if (dynamic_cast<BoneBow*>(weapon) != nullptr)
	{
		projectile = BoneArrow::create();
	}
	else if (dynamic_cast<CrystalBow*>(weapon) != nullptr)
	{
		projectile = CrystalArrow::create();
	}
	else if (dynamic_cast<DemonicBow*>(weapon) != nullptr)
	{
		projectile = DemonicArrow::create();
	}
	else if (dynamic_cast<GoldenBow*>(weapon) != nullptr)
	{
		projectile = GoldenArrow::create();
	}
	else if (dynamic_cast<HuntersBow*>(weapon) != nullptr)
	{
		projectile = HuntersArrow::create();
	}
	else if (dynamic_cast<IvyBow*>(weapon) != nullptr)
	{
		projectile = IvyArrow::create();
	}
	else if (dynamic_cast<SteelBow*>(weapon) != nullptr)
	{
		projectile = SteelArrow::create();
	}
	else if (dynamic_cast<VoidBow*>(weapon) != nullptr)
	{
		projectile = VoidArrow::create();
	}
	else if (dynamic_cast<WoodenBow*>(weapon) != nullptr)
	{
		projectile = WoodenArrow::create();
	}
	// Wands
	else if (dynamic_cast<Wand*>(weapon) != nullptr)
	{
		projectile = EnergyBolt::create();
	}

	if (projectile != nullptr)
	{
		projectile->setMovementMode(Projectile::MovementMode::RotationVelocity);
		projectile->setProjectileRotation(this->squally->isFlippedX() ? 180.0f : 0.0f);
	}

	return projectile;
}

void SquallyOutOfCombatAttackBehavior::decorateProjectile(Projectile* projectile)
{
	super::decorateProjectile(projectile);

	if (projectile == nullptr)
	{
		return;
	}

	projectile->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionData collisionData)
	{
		if (!this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return CollisionResult::DoNothing;
		}

		PlatformerEnemy* enemy = GameUtils::GetFirstParentOfType<PlatformerEnemy>(collisionData.other);

		if (enemy != nullptr && enemy->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			// Encountered enemy w/ first-strike
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, true));
		}

		return CollisionResult::DoNothing;
	});
}
