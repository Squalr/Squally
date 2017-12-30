#include "Shroom.h"

Shroom* Shroom::create()
{
	Shroom* player = new Shroom();

	player->autorelease();

	return player;
}

Shroom::Shroom()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 4000.0f;

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Shroom_ShroomWalking1);
	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_Enemy, true);
	this->addChild(this->sprite);

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;
}

Shroom::~Shroom()
{
}

void Shroom::update(float dt)
{
	Entity::update(dt);

	this->movement.y = 0.0f;

	if (this->movement.x > 0.0f)
	{
		this->sprite->setFlippedX(true);
	}
	else
	{
		this->sprite->setFlippedX(false);
	}
}

bool Shroom::contactBegin(CollisionData data)
{
	return false;
}

bool Shroom::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
		if (data.normal.y < Entity::normalJumpThreshold)
		{
			this->isOnGround = true;
		}

		switch (data.direction)
		{
		case CollisionDirection::Left:
			this->movement.x = 1.0f;
			break;
		case CollisionDirection::Right:
			this->movement.x = -1.0f;
			break;
		case CollisionDirection::StepLeft:
		case CollisionDirection::StepRight:
			this->movement.y = 0.1f;
			break;
		}
		return true;
	}

	return false;
}

bool Shroom::contactEnd(CollisionData data)
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
