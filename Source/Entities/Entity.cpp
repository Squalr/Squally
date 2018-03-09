#include "Entity.h"

Entity::Entity() : CollisionObject::CollisionObject()
{
	this->actualGravityAcceleration = Entity::gravityAcceleration;
	this->actualJumpLaunchVelocity = Entity::jumpLaunchVelocity;
	this->actualMaxFallSpeed = Entity::maxFallSpeed;

	this->isOnGround = false;
	this->movement = Vec2(0, 0);
}

Entity::~Entity()
{
}

void Entity::onEnter()
{
	CollisionObject::onEnter();

	this->scheduleUpdate();
}

void Entity::update(float dt)
{
	CollisionObject::update(dt);

	Vec2 velocity = this->getVelocity();

	velocity.x += this->movement.x * Entity::moveAcceleration * dt;

	if (this->isOnGround)
	{
		velocity.x *= Entity::groundDragFactor;
	}
	else
	{
		velocity.x *= Entity::airDragFactor;
	}

	// Gravity
	if (this->isOnGround)
	{
		if (this->movement.y > 0.0f)
		{
			velocity.y = this->movement.y * this->actualJumpLaunchVelocity;
			this->isOnGround = false;
		}
	}
	else
	{
		velocity.y -= this->actualGravityAcceleration * dt;
	}

	// Prevent fast speeds
	velocity.x = MathUtils::clamp(velocity.x, -this->maxMoveSpeed, this->maxMoveSpeed);
	velocity.y = MathUtils::clamp(velocity.y, -this->maxFallSpeed, this->maxFallSpeed);

	// Apply velocity
	this->setVelocity(velocity);
}

Size Entity::getSize()
{
	return Size(this->spriteNode->getContentSize().width * this->spriteNode->getScaleX(), this->spriteNode->getContentSize().height* this->spriteNode->getScaleY());
}
