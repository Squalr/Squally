#include "ThrowPepperBomb.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/PepperBomb/PepperBomb.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowPepperBomb* ThrowPepperBomb::create(Priority priority)
{
	ThrowPepperBomb* instance = new ThrowPepperBomb(priority);

	instance->autorelease();

	return instance;
}

ThrowPepperBomb::ThrowPepperBomb(Priority priority)
	: super(AttackType::Damage, ItemResources::Consumables_Combat_T4_PepperBomb, priority, AbilityType::Physical, PepperBomb::DamageMin, PepperBomb::DamageMax, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);
	this->explosionSound = WorldSound::create(SoundResources::Platformer_FX_Explosions_Explosion1);

	this->addChild(this->throwSound);
	this->addChild(this->explosionSound);
}

ThrowPepperBomb::~ThrowPepperBomb()
{
}

PlatformerAttack* ThrowPepperBomb::cloneInternal()
{
	return ThrowPepperBomb::create(this->priority);
}

LocalizedString* ThrowPepperBomb::getString()
{
	return Strings::Items_Consumables_Combat_PepperBomb::create();
}

LocalizedString* ThrowPepperBomb::getDescription()
{
	return Strings::Items_Consumables_Combat_BombDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(PepperBomb::DamageMin)),
			ConstantString::create(std::to_string(PepperBomb::DamageMax))
		});
}

std::string ThrowPepperBomb::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowPepperBomb::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowPepperBomb::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (PlatformerEntity* next : targets)
	{
		ThrownObject* bomb = ThrownObject::create(owner, next, false, this->getIconResource(), CSize(64.0f, 64.0f));
		
		bomb->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			bomb->disable(true);
			
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				int damage = RandomHelper::random_int(PepperBomb::DamageMin, PepperBomb::DamageMax);
				this->explosionSound->play();
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, entity, damage, this->abilityType));
			}
			
			SmartAnimationSequenceNode* explosionFx = SmartAnimationSequenceNode::create();

			GameUtils::setWorldCoords3D(explosionFx, GameUtils::getWorldCoords3D(bomb));

			ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
				owner,
				explosionFx,
				SpawnMethod::TopMost,
				PositionMode::Retain,
				[&]()
				{
					explosionFx->playAnimation(FXResources::ExplosionMedium_ExplosionMedium_0000, 0.05f, true);
				},
				[&]()
				{
				}
			));

			return CollisionResult::DoNothing;
		});

		this->replaceOffhandWithProjectile(owner, bomb);

		next->getComponent<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			if (owner == next)
			{
				// Self launch (aim above self)
				bomb->launchTowardsTarget3D(behavior->getTarget(), Vec2(0.0f, 384.0f), 0.25f, Vec3(0.0f, 0.5f, 0.0f));
			}
			else
			{
				bomb->launchTowardsTarget3D(behavior->getTarget(), Vec2::ZERO, 0.25f, Vec3(0.5f, 0.5f, 0.5f));
			}
		});
	}
}

void ThrowPepperBomb::onCleanup()
{
}
