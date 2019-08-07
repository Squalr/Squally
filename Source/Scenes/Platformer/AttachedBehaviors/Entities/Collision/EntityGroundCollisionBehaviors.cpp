#include "EntityGroundCollisionBehaviors.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityGroundCollisionBehaviors::MapKeyAttachedBehavior = "entity-ground-collisions";
const float EntityGroundCollisionBehaviors::GroundCollisionPadding = 28.0f;
const float EntityGroundCollisionBehaviors::GroundCollisionOffset = -4.0f;
const float EntityGroundCollisionBehaviors::GroundCollisionRadius = 8.0f;

EntityGroundCollisionBehaviors* EntityGroundCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityGroundCollisionBehaviors* instance = new EntityGroundCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityGroundCollisionBehaviors::EntityGroundCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityGroundCollisionBehaviors::~EntityGroundCollisionBehaviors()
{
}

void EntityGroundCollisionBehaviors::onLoad()
{
	this->groundCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(std::max((this->entity->entitySize).width - EntityGroundCollisionBehaviors::GroundCollisionPadding * 2.0f, 8.0f), 40.0f),
			1.0f,
			EntityGroundCollisionBehaviors::GroundCollisionRadius
		),
		(int)PlatformerCollisionType::GroundDetector,
		false,
		false
	);

	float offsetY = 0.0f;

	this->groundCollision->getPhysicsBody()->setPositionOffset(this->entity->entityCollisionOffset + Vec2(0.0f, -this->entity->hoverHeight / 2.0f + EntityGroundCollisionBehaviors::GroundCollisionOffset));
	
	this->entity->addChild(this->groundCollision);

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Clear current animation
		if (!this->entity->isDead() && this->entity->getStateOrDefault(StateKeys::VelocityY, Value(0.0f)).asFloat() <= 0.0f)
		{
			this->entity->animationNode->playAnimation("Idle");
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->groundCollision->whenStopsCollidingWith({ (int)EngineCollisionTypes::Intersection }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->groundCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

bool EntityGroundCollisionBehaviors::isOnGround()
{
	return !this->groundCollision->getCurrentCollisions().empty();
}

bool EntityGroundCollisionBehaviors::isStandingOnSomethingOtherThan(CollisionObject* collisonObject)
{
	Node* currentCollisionGroup = collisonObject->getParent();
	std::vector<CollisionObject*> groundCollisions = this->groundCollision->getCurrentCollisions();

	// Special case when standing on an intersection -- always collide with the non-owner of that intersection point (the lower platform)
	for (auto it = groundCollisions.begin(); it != groundCollisions.end(); it++)
	{
		switch((*it)->getCollisionType())
		{
			case (int)EngineCollisionTypes::Intersection:
			{
				return currentCollisionGroup == (*it)->getParent();
			}
			default:
			{
				break;
			}
		}
	}

	// Greedy search for the oldest collision. This works out as being the object that is the true "ground".
	for (auto it = groundCollisions.begin(); it != groundCollisions.end(); it++)
	{
		switch((*it)->getCollisionType())
		{
			case (int)PlatformerCollisionType::Solid:
			case (int)PlatformerCollisionType::PassThrough:
			{
				// Do a parent check because multiple collison objects can be nested under the same macro-object (ie terrain segments)
				if ((*it)->getParent() != currentCollisionGroup)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			default:
			{
				break;
			}
		}
	}

	return false;
}
