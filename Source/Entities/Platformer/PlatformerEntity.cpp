#include "PlatformerEntity.h"

PlatformerEntity::PlatformerEntity(ValueMap* initProperties, std::string scmlResource, PlatformerCollisionType collisionType, Size size, float scale, Vec2 collisionOffset) :
	CollisionObject(
		initProperties,
		PhysicsBody::createBox(PlatformerEntity::convertTotalSizeToCapsuleInnerSegmentSize(size, scale)),
		(CollisionType)(int)collisionType,
		true,
		false
	)
{
	this->size = size;

	float capsuleRadius = (this->size.width / 2.0f) * scale;
	float halfHeight = (this->size.height / 2.0f) * scale;

	// Add the capsule ends
	this->addPhysicsShape(PhysicsShapeCircle::create(capsuleRadius, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0.0f, -halfHeight + capsuleRadius)));
	this->addPhysicsShape(PhysicsShapeCircle::create(capsuleRadius, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0.0f, halfHeight - capsuleRadius)));

	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 1280.0f;
	this->moveAcceleration = 14000.0f;

	this->isOnGround = false;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");

	animationNode->setPosition(collisionOffset * scale);

	// Update width to be serialized
	if (this->properties != nullptr)
	{
		(*this->properties)[PlatformerEntity::MapKeyWidth] = size.width * scale;
		(*this->properties)[PlatformerEntity::MapKeyHeight] = size.height * scale;
	}

	this->addChild(this->animationNode);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	CollisionObject::onEnter();

	this->scheduleUpdate();

	this->initializeCollisionEvents();
}

void PlatformerEntity::update(float dt)
{
	CollisionObject::update(dt);

	Vec2 velocity = this->getVelocity();

	velocity.x += this->movement.x * PlatformerEntity::moveAcceleration * dt;

	if (this->isOnGround)
	{
		velocity.x *= PlatformerEntity::groundDragFactor;
	}
	else
	{
		velocity.x *= PlatformerEntity::airDragFactor;
	}

	// Gravity
	if (this->isOnGround)
	{
		if (this->movement.y > 0.0f)
		{
			velocity.y = this->movement.y * this->actualJumpLaunchVelocity;
			this->isOnGround = false;

			this->animationNode->playAnimation("Jump");
		}
	}

	// Prevent fast speeds
	velocity.x = MathUtils::clamp(velocity.x, -this->maxMoveSpeed, this->maxMoveSpeed);
	velocity.y = MathUtils::clamp(velocity.y, -this->maxFallSpeed, this->maxFallSpeed);

	// Apply velocity
	this->setVelocity(velocity);

	// Update flip
	if (this->animationNode != nullptr)
	{
		if (this->movement.x < 0.0f)
		{
			this->animationNode->setFlippedX(true);
		}
		else if (this->movement.x > 0.0f)
		{
			this->animationNode->setFlippedX(false);
		}
	}
}

void PlatformerEntity::initializeCollisionEvents()
{
	this->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionData collisionData)
	{
		switch (collisionData.direction)
		{
			case CollisionDirection::Down:
			{
				this->isOnGround = true;
				break;
			}
			case CollisionDirection::Left:
			{
				this->movement.x = 1.0f;
				break;
			}
			case CollisionDirection::Right:
			{
				this->movement.x = -1.0f;
				break;
			}
			case CollisionDirection::StepLeft:
			case CollisionDirection::StepRight:
			{
				this->movement.y = 0.5f;
				break;
			}
		}

		return CollisionResult::CollideWithPhysics;
	});

	this->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionData collisionData)
	{
		this->isOnGround = false;

		return CollisionResult::CollideWithPhysics;
	});
}

Size PlatformerEntity::getSize()
{
	return this->size;
}

Size PlatformerEntity::convertTotalSizeToCapsuleInnerSegmentSize(Size size, float scale)
{
	Size newSize = size * scale;
	float capsuleRadius = newSize.width / 2.0f;

	newSize.height = std::max(newSize.height - capsuleRadius * 2.0f, 0.0f);

	return newSize;
}