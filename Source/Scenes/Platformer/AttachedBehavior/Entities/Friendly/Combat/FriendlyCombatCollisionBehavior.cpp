#include "FriendlyCombatCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectile.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string FriendlyCombatCollisionBehavior::MapKeyAttachedBehavior = "friendly-combat-collisions";

FriendlyCombatCollisionBehavior* FriendlyCombatCollisionBehavior::create(GameObject* owner)
{
	FriendlyCombatCollisionBehavior* instance = new FriendlyCombatCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyCombatCollisionBehavior::FriendlyCombatCollisionBehavior(GameObject* owner) : super(owner, (CollisionType)CombatCollisionType::EntityFriendly)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

FriendlyCombatCollisionBehavior::~FriendlyCombatCollisionBehavior()
{
}

void FriendlyCombatCollisionBehavior::onLoad()
{
    super::onLoad();

	this->entityCollision->whenCollidesWith({ (int)CombatCollisionType::Projectile, (int)CombatCollisionType::ProjectileEnemyOnly }, [=](CollisionObject::CollisionData collisionData)
	{
		if (!this->entity->getStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		Projectile* projectile = GameUtils::getFirstParentOfType<Projectile>(collisionData.other, true);

		if (projectile != nullptr)
		{
			projectile->onCollideWithTarget(this->entity);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}
