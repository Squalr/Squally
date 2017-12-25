#include "Entity.h"

Entity::Entity()
{
	this->actualGravityAcceleration = Entity::gravityAcceleration;
	this->actualJumpLaunchVelocity = Entity::jumpLaunchVelocity;
	this->actualMaxFallSpeed = Entity::maxFallSpeed;

	this->isOnGround = false;
	this->movement = Vec2(0, 0);
	this->velocity = Vec2(0, 0);
	this->scheduleUpdate();
}

Entity::~Entity()
{
}

void Entity::onEnter()
{
	Node::onEnter();
}

void Entity::update(float dt)
{
	Node::update(dt);

	this->velocity.x += this->movement.x * Entity::moveAcceleration * dt;

	if (this->isOnGround)
	{
		this->velocity.x *= Entity::groundDragFactor;
	}
	else
	{
		this->velocity.x *= Entity::airDragFactor;
	}

	// Gravity
	if (!this->isOnGround)
	{
		this->velocity.y -= this->actualGravityAcceleration * dt;
	}

	// Prevent fast speeds
	//this->velocity.x = MathHelper.Clamp(Velocity.X, -MaxMoveSpeed, MaxMoveSpeed);
	//this->velocity.y = MathHelper.Clamp(Velocity.Y, -ActualMaxFallSpeed, ActualMaxFallSpeed);

	// Apply velocity
	this->setPosition(this->getPosition() + this->velocity * dt);
}

float Entity::GetWidth()
{
	return this->sprite->getContentSize().width;
}

float Entity::GetHeight()
{
	return this->sprite->getContentSize().height;
}
