#include "GhostBolts.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/GhostBolt/GhostBolt.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

GhostBolts* GhostBolts::create(float attackDuration, float recoverDuration, Priority priority)
{
	GhostBolts* instance = new GhostBolts(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

GhostBolts::GhostBolts(float attackDuration, float recoverDuration, Priority priority)
	: super(AttackType::Damage, UIResources::Menus_Icons_GhostBolts, priority, AbilityType::Shadow, 25, 29, 12, attackDuration, recoverDuration, TargetingType::Multi)
{
}

GhostBolts::~GhostBolts()
{
}

PlatformerAttack* GhostBolts::cloneInternal()
{
	return GhostBolts::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* GhostBolts::getString()
{
	// Not user facing
	return Strings::TODO::create();
}

std::string GhostBolts::getAttackAnimation()
{
	return "AttackCast";
}

void GhostBolts::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (PlatformerEntity* next : targets)
	{
		SmartAnimationSequenceNode* ghostBoltsCastFx = SmartAnimationSequenceNode::create();
		GhostBolt* ghostBolt = GhostBolt::create(owner, next);

		ghostBolt->runSpawnFX();

		ghostBolt->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);
			
			if (!entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				return CollisionResult::DoNothing;
			}

			ghostBolt->disable(true);
			ghostBolt->runImpactFX();

			if (entity != nullptr)
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage(), this->abilityType));
			}

			ghostBolt->despawn(1.0f);

			return CollisionResult::DoNothing;
		});

		ghostBoltsCastFx->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
		ghostBoltsCastFx->setFlippedX(owner->isFlippedX());

		ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
			owner,
			ghostBolt,
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
			ghostBoltsCastFx,
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
		ghostBolt->setPosition3D(GameUtils::getWorldCoords3D(owner) + Vec3(flipMultiplier * 96.0f, 96.0f, 0.0f));
		ghostBoltsCastFx->setPosition3D(GameUtils::getWorldCoords3D(ghostBolt) + Vec3(flipMultiplier * 180.0f, 0.0f, 0.0f));

		next->getComponent<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			ghostBolt->launchTowardsTarget3D(behavior->getTarget(), Vec2::ZERO, 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
		});
	}
}

void GhostBolts::onCleanup()
{
}
