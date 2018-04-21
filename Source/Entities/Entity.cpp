#include "Entity.h"

Entity::Entity(std::string scmlResource, std::string entityName, bool isFlying, Size size, float scale, Vec2 collisionOffset) : CollisionObject::CollisionObject()
{
	this->animationNode = AnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);

	SpriterEngine::EntityInstance* entity = this->animationNode->play(entityName);
	entity->setCurrentAnimation("Idle");

	// TODO: Configurable/randomizable start direction (if any)
	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->actualGravityAcceleration = Entity::gravityAcceleration;
	this->actualJumpLaunchVelocity = Entity::jumpLaunchVelocity;
	this->actualMaxFallSpeed = Entity::maxFallSpeed;
	this->moveAcceleration = Entity::moveAcceleration;

	this->isOnGround = false;
	this->movement = Vec2(0, 0);

	this->size = size;

	animationNode->setPosition(collisionOffset * scale);

	this->addChild(this->animationNode);
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

	// Update flip
	if (this->animationNode != nullptr)
	{
		if (this->movement.x < 0.0f)
		{
			this->animationNode->setFlippedX(true);
		}
		else
		{
			this->animationNode->setFlippedX(false);
		}
	}
}

Size Entity::getSize()
{
	return this->size;
}

bool Entity::contactBegin(CollisionData data)
{
	return false;
}

bool Entity::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
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

bool Entity::contactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		this->isOnGround = false;
		return true;
	}

	return false;
}
