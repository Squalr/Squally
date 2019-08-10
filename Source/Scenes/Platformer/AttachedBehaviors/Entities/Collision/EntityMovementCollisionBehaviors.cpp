#include "EntityMovementCollisionBehaviors.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityGroundCollisionBehaviors.h"
#include "Scenes/Platformer/State/StateKeys.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementCollisionBehaviors::MapKeyAttachedBehavior = "entity-movement-collisions";
const float EntityMovementCollisionBehaviors::WallDetectorSize = 64.0f;
const float EntityMovementCollisionBehaviors::WaterJumpVelocity = 7680.0f;
const float EntityMovementCollisionBehaviors::SwimVerticalDrag = 0.93f;

EntityMovementCollisionBehaviors* EntityMovementCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityMovementCollisionBehaviors* instance = new EntityMovementCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityMovementCollisionBehaviors::EntityMovementCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->movementCollision = nullptr;
	this->leftCollision = nullptr;
	this->rightCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityMovementCollisionBehaviors::~EntityMovementCollisionBehaviors()
{
}

void EntityMovementCollisionBehaviors::onLoad()
{
	this->buildMovementCollision();
	this->buildWallDetectors();
}

void EntityMovementCollisionBehaviors::update(float dt)
{
	super::update(dt);
}

Vec2 EntityMovementCollisionBehaviors::getVelocity()
{
	return this->movementCollision->getVelocity();
}

void EntityMovementCollisionBehaviors::setVelocity(Vec2 velocity)
{
	this->movementCollision->setVelocity(velocity);
}

bool EntityMovementCollisionBehaviors::hasLeftWallCollision()
{
	return !this->leftCollision->getCurrentCollisions().empty();
}

bool EntityMovementCollisionBehaviors::hasRightWallCollision()
{
	return !this->rightCollision->getCurrentCollisions().empty();
}

void EntityMovementCollisionBehaviors::buildMovementCollision()
{
	CollisionType collisionType = CollisionType(PlatformerCollisionType::Movement);

	if (static_cast<Squally*>(this->entity) == nullptr)
	{
		collisionType = CollisionType(PlatformerCollisionType::PlayerMovement);
	}

	this->movementCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->entity->movementSize, 1.0f, 8.0f),
		collisionType,
		true,
		false
	);

	this->movementCollision->bindTo(this->entity);
	this->movementCollision->getPhysicsBody()->setPositionOffset(this->entity->entityCollisionOffset + Vec2(0.0f, this->entity->entitySize.height / 2.0f));

	this->entity->entityCollision->getPhysicsBody()->setPositionOffset(this->entity->entityCollisionOffset + Vec2(0.0f, this->entity->movementSize.height / 2.0f));

	this->addChild(this->movementCollision);

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		EntityGroundCollisionBehaviors* groundBehaviors = this->entity->getAttachedBehavior<EntityGroundCollisionBehaviors>();

		if (groundBehaviors == nullptr)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		// No collision when not standing on anything, or if already on a different platform
		if (!groundBehaviors->isOnGround() || groundBehaviors->isStandingOnSomethingOtherThan(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->movementCollision->setGravityEnabled(false);
		this->entity->controlState = PlatformerEntity::ControlState::Swimming;
		this->movementCollision->setVerticalDampening(EntityMovementCollisionBehaviors::SwimVerticalDrag);

		// Clear current animation
		this->entity->animationNode->playAnimation("Idle");
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->movementCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->movementCollision->setGravityEnabled(true);
		this->entity->controlState = PlatformerEntity::ControlState::Normal;
		this->movementCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);

		// Animate jumping out of water
		if (this->movementCollision->getVelocity().y > 0.0f)
		{
			// Give a velocity boost for jumping out of water
			this->movementCollision->setVelocity(Vec2(this->movementCollision->getVelocity().x, EntityMovementCollisionBehaviors::WaterJumpVelocity));

			this->entity->animationNode->playAnimation("Jump");
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityMovementCollisionBehaviors::buildWallDetectors()
{
	this->leftCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(Size(EntityMovementCollisionBehaviors::WallDetectorSize, this->entity->entitySize.height), 1.0f, 8.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);
	this->rightCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(Size(EntityMovementCollisionBehaviors::WallDetectorSize, this->entity->entitySize.height), 1.0f, 8.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);


	this->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->leftCollision->getPhysicsBody()->setPositionOffset(this->entity->entityCollisionOffset + Vec2(-this->entity->entitySize.width / 2.0f + EntityMovementCollisionBehaviors::WallDetectorSize / 2.0f, this->entity->entitySize.height / 2.0f + this->entity->hoverHeight / 2.0f));
	this->rightCollision->getPhysicsBody()->setPositionOffset(this->entity->entityCollisionOffset + Vec2(this->entity->entitySize.width / 2.0f - EntityMovementCollisionBehaviors::WallDetectorSize / 2.0f, this->entity->entitySize.height / 2.0f + this->entity->hoverHeight / 2.0f));

	this->entity->addChild(this->leftCollision);
	this->entity->addChild(this->rightCollision);
}
