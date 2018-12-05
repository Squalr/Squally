#include "PlatformerEntity.h"

PlatformerEntity::PlatformerEntity(ValueMap* initProperties, std::string scmlResource, CategoryName categoryName, Size size, float scale, Vec2 collisionOffset) :
	CollisionObject(
		initProperties,
		PhysicsBody::createBox(size * scale),
		categoryName,
		true,
		false
	)
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 14000.0f;

	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");

	this->isOnGround = false;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->size = size;

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

Size PlatformerEntity::getSize()
{
	return this->size;
}

bool PlatformerEntity::contactBegin(CollisionData data)
{
	return false;
}

bool PlatformerEntity::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case PlatformerCollisionMapping::CategoryGroupType::G_SolidNpc:
	case PlatformerCollisionMapping::CategoryGroupType::G_SolidFlyingNpc:
	case PlatformerCollisionMapping::CategoryGroupType::G_Solid:
		switch (data.direction)
		{
		case CollisionDirection::Down:
			this->isOnGround = true;
			break;
		case CollisionDirection::Left:
			this->movement.x = 1.0f;
			break;
		case CollisionDirection::Right:
			this->movement.x = -1.0f;
			break;
		case CollisionDirection::StepLeft:
		case CollisionDirection::StepRight:
			this->movement.y = 0.5f;
			break;
		}
		return true;
	}

	return false;
}

bool PlatformerEntity::contactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case PlatformerCollisionMapping::CategoryGroupType::G_Solid:
	case PlatformerCollisionMapping::CategoryGroupType::G_SolidNpc:
	case PlatformerCollisionMapping::CategoryGroupType::G_SolidFlyingNpc:
		this->isOnGround = false;
		return true;
	}

	return false;
}
