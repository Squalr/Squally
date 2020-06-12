#include "ThrowWeapon.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowWeapon* ThrowWeapon::create(float attackDuration, float recoverDuration, Priority priority)
{
	ThrowWeapon* instance = new ThrowWeapon(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

ThrowWeapon::ThrowWeapon(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_SwordStrike, priority, 5, 7, 4, attackDuration, recoverDuration)
{
}

ThrowWeapon::~ThrowWeapon()
{
}

PlatformerAttack* ThrowWeapon::cloneInternal()
{
	return ThrowWeapon::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* ThrowWeapon::getString()
{
	return Strings::Platformer_Combat_Attacks_ThrowWeapon::create();
}

std::string ThrowWeapon::getAttackAnimation()
{
	return "AttackThrow";
}

void ThrowWeapon::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		ThrownObject* weapon = ThrownObject::create(owner, next, false, this->getMainhandResource(owner), Size(64.0f, 128.0f));
	
		weapon->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
		{
			PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);
			
			if (!entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				return CollisionObject::CollisionResult::DoNothing;
			}
			
			weapon->disable(true);

			if (entity != nullptr)
			{
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage()));
			}

			return CollisionObject::CollisionResult::DoNothing;
		});

		this->replaceMainhandWithProjectile(owner, weapon);

		next->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			weapon->launchTowardsTarget3D(behavior->getTarget(), Vec2::ZERO, 2.0f, Vec3(0.5f, 0.5f, 0.5f));
		});

		CombatEvents::TriggerProjectileSpawned(CombatEvents::ProjectileSpawnedArgs(owner, next, weapon));
	}
}

void ThrowWeapon::onCleanup()
{
}
