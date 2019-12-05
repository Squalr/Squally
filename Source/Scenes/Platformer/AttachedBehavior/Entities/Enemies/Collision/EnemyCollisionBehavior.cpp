#include "EnemyCollisionBehavior.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string EnemyCollisionBehavior::MapKeyAttachedBehavior = "enemy-collisions";

EnemyCollisionBehavior* EnemyCollisionBehavior::create(GameObject* owner)
{
	EnemyCollisionBehavior* instance = new EnemyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyCollisionBehavior::EnemyCollisionBehavior(GameObject* owner) : super(owner, (int)PlatformerCollisionType::Enemy)
{
}

EnemyCollisionBehavior::~EnemyCollisionBehavior()
{
}

void EnemyCollisionBehavior::onLoad()
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
