#include "EntityCollisionBehaviors.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityCollisionBehaviors::MapKeyAttachedBehavior = "entity-collisions";

EntityCollisionBehaviors* EntityCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCollisionBehaviors* instance = new EntityCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCollisionBehaviors::EntityCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
}

EntityCollisionBehaviors::~EntityCollisionBehaviors()
{
}

void EntityCollisionBehaviors::onLoad()
{
	this->entity->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->entity->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		// No collision when not standing on anything, or if already on a different platform
		if (this->entity->groundCollision->getCurrentCollisions().empty() || this->entity->isStandingOnSomethingOtherThan(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->entity->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entity->movementCollision->setGravityEnabled(false);
		this->entity->controlState = PlatformerEntity::ControlState::Swimming;
		this->entity->movementCollision->setVerticalDampening(PlatformerEntity::SwimVerticalDrag);

		// Clear current animation
		this->entity->animationNode->playAnimation("Idle");
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->movementCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entity->movementCollision->setGravityEnabled(true);
		this->entity->controlState = PlatformerEntity::ControlState::Normal;
		this->entity->movementCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);

		// Animate jumping out of water
		if (this->entity->movementCollision->getVelocity().y > 0.0f)
		{
			// Give a velocity boost for jumping out of water
			this->entity->movementCollision->setVelocity(Vec2(this->entity->movementCollision->getVelocity().x, PlatformerEntity::JumpVelocity));

			this->entity->animationNode->playAnimation("Jump");
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Clear current animation
		if (!this->entity->isDead() && this->entity->movementCollision->getVelocity().y <= 0.0f)
		{
			this->entity->animationNode->playAnimation("Idle");
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->groundCollision->whenStopsCollidingWith({ (int)EngineCollisionTypes::Intersection }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->groundCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});
}
