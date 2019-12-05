#include "FriendlyCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string FriendlyCollisionBehavior::MapKeyAttachedBehavior = "friendly-collisions";

FriendlyCollisionBehavior* FriendlyCollisionBehavior::create(GameObject* owner)
{
	FriendlyCollisionBehavior* instance = new FriendlyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyCollisionBehavior::FriendlyCollisionBehavior(GameObject* owner) : super(owner, (int)PlatformerCollisionType::FriendlyNpc)
{
}

FriendlyCollisionBehavior::~FriendlyCollisionBehavior()
{
}

void FriendlyCollisionBehavior::onLoad()
{
    super::onLoad();

	this->entity->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* collisionBehavior)
	{
		collisionBehavior->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{	
			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{	
			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
		{	
			return CollisionObject::CollisionResult::CollideWithPhysics;
		});
	});
}
