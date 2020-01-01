#include "DragonBreath.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DragonBreath* DragonBreath::create(float attackDuration, float recoverDuration)
{
	DragonBreath* instance = new DragonBreath(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

DragonBreath::DragonBreath(float attackDuration, float recoverDuration) : super(AttackType::Damage, UIResources::Menus_Icons_FireBalls, 1.5f, 5, 7, 4, attackDuration, recoverDuration)
{
}

DragonBreath::~DragonBreath()
{
}

PlatformerAttack* DragonBreath::cloneInternal()
{
	return DragonBreath::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* DragonBreath::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DragonBreath::getAttackAnimation()
{
	return "AttackDragon";
}

void DragonBreath::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	SmartAnimationSequenceNode* fireballAnim = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);
	SmartAnimationSequenceNode* fireBreath = SmartAnimationSequenceNode::create();
	ThrownObject* fireball = ThrownObject::create(owner, fireballAnim, Size(32.0f, 32.0f));

	fireballAnim->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.05f);
	fireBreath->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
	fireBreath->setFlippedX(owner->isFlippedX());
	
	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, fireball, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, fireBreath, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
	
	fireball->setPosition(GameUtils::getWorldCoords(owner) + Vec2((owner->isFlippedX() ? -96.0f : 96.0f), 96.0f));
	fireBreath->setPosition(GameUtils::getWorldCoords(fireballAnim) + Vec2((owner->isFlippedX() ? -160.0f : 160.0f), 0.0f));

	fireball->getCollision()->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		fireball->getCollision()->setPhysicsEnabled(false);
		fireball->setVisible(false);

		// Explosion animation
		SmartAnimationSequenceNode* explosionAnim = SmartAnimationSequenceNode::create(FXResources::Explosion_Explosion_0000);
		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, explosionAnim, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
		explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);
		explosionAnim->setPosition(GameUtils::getWorldCoords(fireball));

		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	target->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		fireball->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
	});
}

void DragonBreath::onCleanup()
{
}
