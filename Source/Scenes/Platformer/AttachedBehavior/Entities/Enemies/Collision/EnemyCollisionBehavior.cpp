#include "EnemyCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string EnemyCollisionBehavior::MapKey = "enemy-collisions";

EnemyCollisionBehavior* EnemyCollisionBehavior::create(GameObject* owner)
{
	EnemyCollisionBehavior* instance = new EnemyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyCollisionBehavior::EnemyCollisionBehavior(GameObject* owner) : super(owner, (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EntityMovement)
{
}

EnemyCollisionBehavior::~EnemyCollisionBehavior()
{
}

void EnemyCollisionBehavior::onLoad()
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

void EnemyCollisionBehavior::onDisable()
{
	super::onDisable();
}

void EnemyCollisionBehavior::onEntityCollisionCreated()
{
}
