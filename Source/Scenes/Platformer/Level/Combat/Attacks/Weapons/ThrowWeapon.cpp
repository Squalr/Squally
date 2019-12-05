#include "ThrowWeapon.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowWeapon* ThrowWeapon::create(float attackDuration, float recoverDuration)
{
	ThrowWeapon* instance = new ThrowWeapon(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

ThrowWeapon::ThrowWeapon(float attackDuration, float recoverDuration) : super(AttackType::ProjectileDamage, UIResources::Menus_Icons_FireBalls, 0.5f, 5, 7, 4, attackDuration, recoverDuration)
{
}

ThrowWeapon::~ThrowWeapon()
{
}

PlatformerAttack* ThrowWeapon::cloneInternal()
{
	return ThrowWeapon::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* ThrowWeapon::getString()
{
	return Strings::Common_Empty::create();
}

std::string ThrowWeapon::getAttackAnimation()
{
	return "AttackThrow";
}

void ThrowWeapon::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::generateProjectiles(owner, target);

	ThrownObject* weapon = ThrownObject::create(owner, this->getMainhandResource(owner));
	
	weapon->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
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

void ThrowWeapon::onCleanup()
{
}
