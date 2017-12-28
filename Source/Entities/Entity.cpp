#include "Entity.h"

Entity::Entity()
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
	Node::onEnter();
}

void Entity::update(float dt)
{
	Node::update(dt);

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

	//velocity.y += this->actualGravityAcceleration * dt;
	//velocity.y += this->actualGravityAcceleration * dt;

	// Prevent fast speeds
	//this->velocity.x = MathHelper.Clamp(Velocity.X, -MaxMoveSpeed, MaxMoveSpeed);
	//this->velocity.y = MathHelper.Clamp(Velocity.Y, -ActualMaxFallSpeed, ActualMaxFallSpeed);

	// Apply velocity
	this->setVelocity(velocity);
}

bool Entity::contactBegin(CollisionObject* other)
{
	/*

	PhysicsShape* other = Collision::getCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	switch ((Collision::CollisionGroup)other->getContactTestBitmask())
	{
	case Collision::CollisionGroup::Solid:
		if (Collision::isContactBelow(this, contact))
		{
			this->isOnGround = true;
		}
		break;
	case Collision::CollisionGroup::SolidNpc:
		if (this->collisionGroup & Collision::CollisionGroup::Enemy)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}

	return true;
	*/
	return true;
}

bool Entity::contactUpdate(CollisionObject* other)
{
	return true;
}

bool Entity::contactEnd(CollisionObject* other)
{
	/*

	PhysicsShape* other = Collision::getCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	switch ((Collision::CollisionGroup)other->getContactTestBitmask())
	{
	case Collision::CollisionGroup::Solid:
		this->isOnGround = false;
		break;
	case Collision::CollisionGroup::SolidNpc:
		if (this->collisionGroup & Collision::CollisionGroup::Enemy)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}

	return true;
	*/
	return true;
}

float Entity::getWidth()
{
	return this->sprite->getContentSize().width;
}

float Entity::getHeight()
{
	return this->sprite->getContentSize().height;
}
