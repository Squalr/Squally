#include "ThrowFlamingWeapon.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
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

ThrowFlamingWeapon* ThrowFlamingWeapon::create(float attackDuration, float recoverDuration, float priority)
{
	ThrowFlamingWeapon* instance = new ThrowFlamingWeapon(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

ThrowFlamingWeapon::ThrowFlamingWeapon(float attackDuration, float recoverDuration, float priority) : super(AttackType::Damage, UIResources::Menus_Icons_FireBalls, priority, 5, 7, 4, attackDuration, recoverDuration)
{
}

ThrowFlamingWeapon::~ThrowFlamingWeapon()
{
}

PlatformerAttack* ThrowFlamingWeapon::cloneInternal()
{
	return ThrowFlamingWeapon::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* ThrowFlamingWeapon::getString()
{
	return Strings::Platformer_Combat_Attacks_ThrowFlamingWeapon::create();
}

std::string ThrowFlamingWeapon::getAttackAnimation()
{
	return "AttackThrow";
}

void ThrowFlamingWeapon::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	ThrownObject* weapon = ThrownObject::create(owner, this->getMainhandResource(owner), Size(64.0f, 128.0f));
	SmartAnimationSequenceNode* fire = SmartAnimationSequenceNode::create(FXResources::TorchFire_TorchFire_0000);

	weapon->addChild(fire);

	fire->playAnimationRepeat(FXResources::TorchFire_TorchFire_0000, 0.005f);
	fire->setPosition(Vec2(0.0f, 56.0f));
	
	weapon->getCollision()->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		weapon->getCollision()->setPhysicsEnabled(false);

		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->replaceMainhandWithProjectile(owner, weapon);

	target->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		weapon->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 2.0f, Vec3(0.5f, 0.5f, 0.5f));
	});
}

void ThrowFlamingWeapon::onCleanup()
{
}
