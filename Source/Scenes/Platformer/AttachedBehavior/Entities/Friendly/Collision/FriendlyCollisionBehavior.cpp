#include "FriendlyCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string FriendlyCollisionBehavior::MapKey = "friendly-collisions";

FriendlyCollisionBehavior* FriendlyCollisionBehavior::create(GameObject* owner)
{
	FriendlyCollisionBehavior* instance = new FriendlyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyCollisionBehavior::FriendlyCollisionBehavior(GameObject* owner) : super(owner, (int)PlatformerCollisionType::Entity, (int)PlatformerCollisionType::EntityMovement)
{
}

FriendlyCollisionBehavior::~FriendlyCollisionBehavior()
{
}

void FriendlyCollisionBehavior::onLoad()
{
    super::onLoad();

	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* collisionBehavior)
	{
		if (collisionBehavior->leftCollision != nullptr)
		{
			collisionBehavior->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
			{	
				return CollisionObject::CollisionResult::DoNothing;
			});
		}

		if (collisionBehavior->rightCollision != nullptr)
		{
			collisionBehavior->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
			{	
				return CollisionObject::CollisionResult::DoNothing;
			});
		}

		if (collisionBehavior->entityCollision != nullptr)
		{
			collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidNpcOnly }, [=](CollisionObject::CollisionData collisionData)
			{	
				return CollisionObject::CollisionResult::CollideWithPhysics;
			});
		}
	});
}

void FriendlyCollisionBehavior::onDisable()
{
	super::onDisable();
}

void FriendlyCollisionBehavior::onEntityCollisionCreated()
{
}
