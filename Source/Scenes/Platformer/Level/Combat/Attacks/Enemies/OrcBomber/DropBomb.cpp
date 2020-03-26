#include "DropBomb.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Projectiles/Combat/Fireball/Fireball.h"
#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DropBomb* DropBomb::create(float attackDuration, float recoverDuration, Priority priority)
{
	DropBomb* instance = new DropBomb(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

DropBomb::DropBomb(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_FireBalls, priority, 7, 9, 12, attackDuration, recoverDuration)
{
}

DropBomb::~DropBomb()
{
}

PlatformerAttack* DropBomb::cloneInternal()
{
	return DropBomb::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* DropBomb::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DropBomb::getAttackAnimation()
{
	return "DropBomb";
}

void DropBomb::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	SmartAnimationSequenceNode* fireBreath = SmartAnimationSequenceNode::create();
	Fireball* fireball = Fireball::create(owner, target);

	fireball->runSpawnFX();

	fireball->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		fireball->disable(false);
		fireball->runImpactFX();

		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	fireBreath->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
	fireBreath->setFlippedX(owner->isFlippedX());

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		owner,
		fireball,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));
	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		owner,
		fireBreath,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));
	
	fireball->setPosition3D(GameUtils::getWorldCoords3D(owner) + Vec3((owner->isFlippedX() ? -96.0f : 96.0f), 96.0f, 0.0f));
	fireBreath->setPosition3D(GameUtils::getWorldCoords3D(fireball) + Vec3((owner->isFlippedX() ? -180.0f : 180.0f), 0.0f, 0.0f));

	target->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		fireball->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
	});
}

void DropBomb::onCleanup()
{
}
