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

ThrowFlamingWeapon* ThrowFlamingWeapon::create(float attackDuration, float recoverDuration)
{
	ThrowFlamingWeapon* instance = new ThrowFlamingWeapon(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

ThrowFlamingWeapon::ThrowFlamingWeapon(float attackDuration, float recoverDuration) : super(AttackType::ProjectileDamage, UIResources::Menus_Icons_FireBalls, 0.5f, 5, 7, 4, attackDuration, recoverDuration)
{
}

ThrowFlamingWeapon::~ThrowFlamingWeapon()
{
}

PlatformerAttack* ThrowFlamingWeapon::cloneInternal()
{
	return ThrowFlamingWeapon::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* ThrowFlamingWeapon::getString()
{
	return Strings::Platformer_Combat_Attacks_ThrowFlamingWeapon::create();
}

std::string ThrowFlamingWeapon::getAttackAnimation()
{
	return "AttackThrow";
}

void ThrowFlamingWeapon::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	ThrownObject* weapon = ThrownObject::create(owner, this->getMainhandResource(owner));
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
