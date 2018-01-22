#include "Entity.h"

Entity::Entity() : CollisionObject::CollisionObject()
{
	this->actualGravityAcceleration = Entity::gravityAcceleration;
	this->actualJumpLaunchVelocity = Entity::jumpLaunchVelocity;
	this->actualMaxFallSpeed = Entity::maxFallSpeed;

	this->isOnGround = false;
	this->movement = Vec2(0, 0);
	this->scheduleUpdate();
}

Entity::~Entity()
{
}

void Entity::onEnter()
{
	CollisionObject::onEnter();
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
	//this->velocity.x = MathHelper.Clamp(Velocity.X, -MaxMoveSpeed, MaxMoveSpeed);
	//this->velocity.y = MathHelper.Clamp(Velocity.Y, -ActualMaxFallSpeed, ActualMaxFallSpeed);

	// Apply velocity
	this->setVelocity(velocity);
}

float Entity::getWidth()
{
	return this->sprite->getContentSize().width;
}

float Entity::getHeight()
{
	return this->sprite->getContentSize().height;
}
