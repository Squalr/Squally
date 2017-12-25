#include "Entity.h"

Entity::Entity()
{
	this->collisionGroup = Collision::CollisionGroup::Entity;
	this->actualGravityAcceleration = Entity::gravityAcceleration;
	this->actualJumpLaunchVelocity = Entity::jumpLaunchVelocity;
	this->actualMaxFallSpeed = Entity::maxFallSpeed;

	this->isOnGround = false;
	this->movement = Vec2(0, 0);
	this->scheduleUpdate();

	this->InitializeListeners();
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
		velocity.y += this->movement.y * this->actualJumpLaunchVelocity;
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

void Entity::InitializeListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(Entity::OnContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(Entity::OnContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Entity::OnContactEnd, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool Entity::OnContactBegin(PhysicsContact &contact)
{
	PhysicsShape* other = Collision::GetCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}
	if (Collision::IsContactBelow(this, contact))
	{
		this->isOnGround = true;
	}

	switch ((Collision::CollisionGroup)other->getCollisionBitmask())
	{
	case Collision::CollisionGroup::Solid:
		break;
	}

	return true;
}

bool Entity::OnContactUpdate(PhysicsContact &contact)
{
	PhysicsShape* other = Collision::GetCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}
	if (Collision::IsContactBelow(this, contact))
	{
		this->isOnGround = true;
	}

	switch ((Collision::CollisionGroup)other->getCollisionBitmask())
	{
	case Collision::CollisionGroup::Solid:
		break;
	}

	return true;
}

bool Entity::OnContactEnd(PhysicsContact &contact)
{
	PhysicsShape* other = Collision::GetCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}
	this->isOnGround = false;

	switch ((Collision::CollisionGroup)other->getCollisionBitmask())
	{
	case Collision::CollisionGroup::Solid:
		break;
	}

	return true;
}

float Entity::GetWidth()
{
	return this->sprite->getContentSize().width;
}

float Entity::GetHeight()
{
	return this->sprite->getContentSize().height;
}
