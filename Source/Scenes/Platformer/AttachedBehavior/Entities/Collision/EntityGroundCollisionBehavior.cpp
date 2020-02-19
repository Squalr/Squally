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
const float EntityGroundCollisionBehavior::GroundCollisionPadding = 4.0f;
const float EntityGroundCollisionBehavior::GroundCollisionOffset = 8.0f;
const float EntityGroundCollisionBehavior::GroundCollisionHeight = 32.0f;
const float EntityGroundCollisionBehavior::GroundCollisionRadius = 8.0f;
const float EntityGroundCollisionBehavior::CornerCollisionWidth = 32.0f;

EntityGroundCollisionBehavior* EntityGroundCollisionBehavior::create(GameObject* owner)
{
	EntityGroundCollisionBehavior* instance = new EntityGroundCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityGroundCollisionBehavior::EntityGroundCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->groundCollision = nullptr;
	this->leftCornerCollision = nullptr;
	this->rightCornerCollision = nullptr;
	this->detectorWidth = 0.0f;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->detectorWidth = std::max((this->entity->getEntitySize()).width + EntityGroundCollisionBehavior::GroundCollisionPadding * 2.0f, 8.0f);
	}

	this->toggleQueryable(false);
}

EntityGroundCollisionBehavior::~EntityGroundCollisionBehavior()
{
}

void EntityGroundCollisionBehavior::onLoad()
{
	this->defer([=]()
	{
		this->buildGroundCollisionDetector();
		this->buildCornerCollisionDetectors();
		this->toggleQueryable(true);
	});
}

void EntityGroundCollisionBehavior::onCollideWithGround()
{
	// Clear current animation
	if (this->entity->getStateOrDefaultBool(StateKeys::IsAlive, true) && this->entity->getStateOrDefaultFloat(StateKeys::VelocityY, 0.0f) <= 0.0f)
	{
		if (this->entity->getAnimations()->getCurrentAnimation() == "Jump")
		{
			this->entity->getAnimations()->clearAnimationPriority();
		}

		this->entity->getAnimations()->playAnimation();
	}
}

bool EntityGroundCollisionBehavior::isOnGround()
{
	return !this->groundCollision->getCurrentCollisions().empty();
}

bool EntityGroundCollisionBehavior::hasLeftCornerCollision()
{
	return !this->leftCornerCollision->getCurrentCollisions().empty();
}

bool EntityGroundCollisionBehavior::hasRightCornerCollision()
{
	return !this->rightCornerCollision->getCurrentCollisions().empty();
}

bool EntityGroundCollisionBehavior::isStandingOn(CollisionObject* collisonObject)
{
	Node* currentCollisionGroup = collisonObject->getParent();

	// Special case for intersection points -- just return false
	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		switch(next->getCollisionType())
		{
			case (int)EngineCollisionTypes::Intersection:
			{
				return false;
			}
			default:
			{
				break;
			}
		}
	}

	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		switch(next->getCollisionType())
		{
			case (int)PlatformerCollisionType::Solid:
			case (int)PlatformerCollisionType::PassThrough:
			{
				// Do a parent check because multiple collison objects can be nested under the same macro-object (ie terrain segments)
				if (next->getParent() == currentCollisionGroup)
				{
					return true;
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

bool EntityGroundCollisionBehavior::isStandingOnSomethingOtherThan(CollisionObject* collisonObject)
{
	Node* currentCollisionGroup = collisonObject->getParent();

	// Special case when standing on an intersection -- The owner of the intersection point has collision priority, as it is the lower of the platforms.
	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		const Node* otherCollisionGroup = next->getParent();

		switch(next->getCollisionType())
		{
			case (int)EngineCollisionTypes::Intersection:
			{
				return currentCollisionGroup == otherCollisionGroup;
			}
			default:
			{
				break;
			}
		}
	}

	// Greedy search for the oldest collision. This works out as being the object that is the true "ground".
	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		const Node* otherCollisionGroup = next->getParent();

		switch(next->getCollisionType())
		{
			case (int)PlatformerCollisionType::Solid:
			case (int)PlatformerCollisionType::PassThrough:
			{
				// Do a parent check because multiple collison objects can be nested under the same macro-object (ie terrain segments)
				if (otherCollisionGroup != currentCollisionGroup)
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

void EntityGroundCollisionBehavior::buildGroundCollisionDetector()
{
	if (this->groundCollision != nullptr)
	{
		return;
	}

	this->groundCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(this->detectorWidth, EntityGroundCollisionBehavior::GroundCollisionHeight)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, -this->entity->getHoverHeight() / 2.0f - EntityGroundCollisionBehavior::GroundCollisionOffset);

	this->groundCollision->setPosition(offset);

	this->addChild(this->groundCollision);

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		this->onCollideWithGround();
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Intersection }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityGroundCollisionBehavior::buildCornerCollisionDetectors()
{
	if (this->rightCornerCollision != nullptr || this->leftCornerCollision != nullptr)
	{
		return;
	}

	const float Buffer = 4;

	this->rightCornerCollision = CollisionObject::create(
		CollisionObject::createBox(
			Size(EntityGroundCollisionBehavior::CornerCollisionWidth, EntityGroundCollisionBehavior::GroundCollisionHeight + Buffer)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);

	this->leftCornerCollision = CollisionObject::create(
		CollisionObject::createBox(
			Size(EntityGroundCollisionBehavior::CornerCollisionWidth, EntityGroundCollisionBehavior::GroundCollisionHeight + Buffer)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(this->detectorWidth / 2.0f, -this->entity->getHoverHeight() / 2.0f - EntityGroundCollisionBehavior::GroundCollisionOffset);

	this->rightCornerCollision->setPosition(offset);
	this->leftCornerCollision->setPosition(Vec2(-offset.x, offset.y));
	
	this->addChild(this->rightCornerCollision);
	this->addChild(this->leftCornerCollision);

	this->leftCornerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->rightCornerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
