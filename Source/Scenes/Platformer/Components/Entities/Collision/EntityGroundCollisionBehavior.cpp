#include "EntityGroundCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityHoverCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityGroundCollisionBehavior::MapKey = "entity-ground-collisions";
const float EntityGroundCollisionBehavior::GroundCollisionPadding = -4.0f;
const float EntityGroundCollisionBehavior::GroundCollisionOffset = -8.0f;
const float EntityGroundCollisionBehavior::GroundCollisionHeight = 64.0f;
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
	this->hoverCollisionBehavior = nullptr;

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
	this->entity->watchForComponent<EntityHoverCollisionBehavior>([=](EntityHoverCollisionBehavior* hoverCollisionBehavior)
	{
		this->hoverCollisionBehavior = hoverCollisionBehavior;
	});

	this->defer([=]()
	{
		this->buildGroundCollisionDetector();
		// this->buildCornerCollisionDetectors();
		this->toggleQueryable(true);
	});
}

void EntityGroundCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->groundCollision != nullptr)
	{
		this->groundCollision->setPhysicsEnabled(false);
	}
	
	if (this->leftCornerCollision != nullptr)
	{
		this->leftCornerCollision->setPhysicsEnabled(false);
	}
	
	if (this->rightCornerCollision != nullptr)
	{
		this->rightCornerCollision->setPhysicsEnabled(false);
	}
}

CollisionObject* EntityGroundCollisionBehavior::getGroundCollision()
{
	return this->groundCollision;
}

void EntityGroundCollisionBehavior::onCollideWithGround()
{
	// Clear current animation
	if (this->entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true) && this->entity->getRuntimeStateOrDefaultFloat(StateKeys::VelocityY, 0.0f) <= 0.0f)
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
	return this->groundCollision == nullptr ? false : this->groundCollision->hasCollisions();
}

bool EntityGroundCollisionBehavior::hasLeftCornerCollision()
{
	return this->leftCornerCollision == nullptr ? false : this->leftCornerCollision->hasCollisions();
}

bool EntityGroundCollisionBehavior::hasRightCornerCollision()
{
	return this->rightCornerCollision == nullptr ? false : this->rightCornerCollision->hasCollisions();
}

bool EntityGroundCollisionBehavior::isStandingOn(CollisionObject* collisonObject)
{
	if (this->groundCollision == nullptr)
	{
		return false;
	}

	Node* currentCollisionGroup = collisonObject->getParent();

	/*
	// Special case for intersection points -- just return false
	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		if (next->hasCollisionType(CollisionType(PlatformerCollisionType::Intersection)))
		{
			return false;
		}
	}
	*/

	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		if (next->hasCollisionType(CollisionType(PlatformerCollisionType::Solid))
			|| next->hasCollisionType(CollisionType(PlatformerCollisionType::PassThrough)))
		{
			// Do a parent check because multiple collison objects can be nested under the same macro-object (ie terrain segments)
			if (next->getParent() == currentCollisionGroup)
			{
				return true;
			}
		}
	}

	return false;
}

bool EntityGroundCollisionBehavior::isStandingOnSomethingOtherThan(CollisionObject* collisonObject)
{
	if (this->groundCollision == nullptr)
	{
		return false;
	}

	Node* currentCollisionGroup = collisonObject->getParent();

	// Special case when standing on an intersection -- The owner of the intersection point has collision priority, as it is the lower of the platforms.
	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		const Node* otherCollisionGroup = next->getParent();

		if (next->hasCollisionType(CollisionType(PlatformerCollisionType::Intersection)))
		{
			return currentCollisionGroup == otherCollisionGroup;
		}
	}

	// Greedy search for the oldest collision. This works out as being the object that is the true "ground".
	for (auto next : this->groundCollision->getCurrentCollisions())
	{
		const Node* otherCollisionGroup = next->getParent();

		if (next->hasCollisionType(CollisionType(PlatformerCollisionType::Solid))
			|| next->hasCollisionType(CollisionType(PlatformerCollisionType::PassThrough)))
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
	
	this->groundCollision->setPosition(this->entity->getCollisionOffset() + Vec2(0.0f, EntityGroundCollisionBehavior::GroundCollisionOffset));

	this->addChild(this->groundCollision);

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->onCollideWithGround();
		
		return CollisionResult::DoNothing;
	});

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Intersection }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
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
	Vec2 offset = collisionOffset + Vec2(this->detectorWidth / 2.0f,  EntityGroundCollisionBehavior::GroundCollisionOffset);

	this->rightCornerCollision->setPosition(offset);
	this->leftCornerCollision->setPosition(Vec2(-offset.x, offset.y));
	
	this->addChild(this->rightCornerCollision);
	this->addChild(this->leftCornerCollision);

	this->leftCornerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});

	this->rightCornerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});
}
