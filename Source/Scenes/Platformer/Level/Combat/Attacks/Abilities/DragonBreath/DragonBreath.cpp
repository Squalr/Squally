#include "DragonBreath.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/Fireball/Fireball.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DragonBreath* DragonBreath::create(float attackDuration, float recoverDuration, Priority priority)
{
	DragonBreath* instance = new DragonBreath(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

DragonBreath::DragonBreath(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_FireSphere, priority, AbilityType::Fire, 7, 9, 12, attackDuration, recoverDuration)
{
}

DragonBreath::~DragonBreath()
{
}

PlatformerAttack* DragonBreath::cloneInternal()
{
	return DragonBreath::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* DragonBreath::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DragonBreath::getAttackAnimation()
{
	return "AttackDragon";
}

void DragonBreath::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		SmartAnimationSequenceNode* fireBreath = SmartAnimationSequenceNode::create();
		Fireball* fireball = Fireball::create(owner, next);

		fireball->runSpawnFX();

		fireball->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);
			
			if (!entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				return CollisionResult::DoNothing;
			}

			fireball->disable(true);
			fireball->runImpactFX();

			if (entity != nullptr)
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage(), this->abilityType));
			}

			fireball->despawn(1.0f);

			return CollisionResult::DoNothing;
		});

		fireBreath->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
		fireBreath->setFlippedX(owner->isFlippedX());

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			owner,
			fireball,
			SpawnMethod::Above,
			PositionMode::Discard,
			[&]()
			{
			},
			[&]()
			{
			}
		));
		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			owner,
			fireBreath,
			SpawnMethod::Above,
			PositionMode::Discard,
			[&]()
			{
			},
			[&]()
			{
			}
		));
		
		float flipMultiplier = (owner->isFlippedX() ? -1.0f : 1.0f);
		fireball->setPosition3D(GameUtils::getWorldCoords3D(owner) + Vec3(flipMultiplier * 96.0f, 96.0f, 0.0f));
		fireBreath->setPosition3D(GameUtils::getWorldCoords3D(fireball) + Vec3(flipMultiplier * 180.0f, 0.0f, 0.0f));

		next->getComponent<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			fireball->launchTowardsTarget3D(behavior->getTarget(), Vec2::ZERO, 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
		});
	}
}

void DragonBreath::onCleanup()
{
}
