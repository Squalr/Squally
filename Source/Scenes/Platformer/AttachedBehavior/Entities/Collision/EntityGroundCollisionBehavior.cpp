#include "EntityGroundCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityGroundCollisionBehavior::MapKeyAttachedBehavior = "entity-ground-collisions";
const float EntityGroundCollisionBehavior::GroundCollisionPadding = 28.0f;
const float EntityGroundCollisionBehavior::GroundCollisionOffset = -4.0f;
const float EntityGroundCollisionBehavior::GroundCollisionRadius = 8.0f;

EntityGroundCollisionBehavior* EntityGroundCollisionBehavior::create(GameObject* owner)
{
	EntityGroundCollisionBehavior* instance = new EntityGroundCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityGroundCollisionBehavior::EntityGroundCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityGroundCollisionBehavior::~EntityGroundCollisionBehavior()
{
}

void EntityGroundCollisionBehavior::onLoad()
{
	this->groundCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(std::max((this->entity->getEntitySize()).width - EntityGroundCollisionBehavior::GroundCollisionPadding * 2.0f, 8.0f), 40.0f),
			1.0f,
			EntityGroundCollisionBehavior::GroundCollisionRadius
		),
		(int)PlatformerCollisionType::GroundDetector,
		false,
		false
	);

	float offsetY = 0.0f;

	this->groundCollision->getPhysicsBody()->setPositionOffset(this->entity->getCollisionOffset() + Vec2(0.0f, -this->entity->getHoverHeight() / 2.0f + EntityGroundCollisionBehavior::GroundCollisionOffset));
	
	this->addChild(this->groundCollision);

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Clear current animation
		if (this->entity->getStateOrDefaultBool(StateKeys::IsAlive, true) && this->entity->getStateOrDefaultFloat(StateKeys::VelocityY, 0.0f) <= 0.0f)
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

bool EntityGroundCollisionBehavior::isOnGround()
{
	return !this->groundCollision->getCurrentCollisions().empty();
}

bool EntityGroundCollisionBehavior::isStandingOnSomethingOtherThan(CollisionObject* collisonObject)
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
