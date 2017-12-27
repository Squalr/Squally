#include "Entity.h"

Entity::Entity()
{
	this->actualGravityAcceleration = Entity::gravityAcceleration;
	this->actualJumpLaunchVelocity = Entity::jumpLaunchVelocity;
	this->actualMaxFallSpeed = Entity::maxFallSpeed;

	this->isOnGround = false;
	this->movement = Vec2(0, 0);
	this->scheduleUpdate();

	this->initializeListeners();
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

	Vec2 velocity = this->physicsBody->getVelocity();

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
		velocity.y = this->movement.y * this->actualJumpLaunchVelocity;
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
	this->physicsBody->setVelocity(velocity);
}

void Entity::initializeListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(Entity::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(Entity::onContactUpdate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(Entity::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Entity::onContactEnd, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool Entity::onContactBegin(PhysicsContact &contact)
{
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
}

bool Entity::onContactUpdate(PhysicsContact &contact)
{
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
}

bool Entity::onContactEnd(PhysicsContact &contact)
{
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
}

float Entity::getWidth()
{
	return this->sprite->getContentSize().width;
}

float Entity::getHeight()
{
	return this->sprite->getContentSize().height;
}
