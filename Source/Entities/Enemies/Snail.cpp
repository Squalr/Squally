#include "Snail.h"

Snail* Snail::create()
{
	Snail* snail = new Snail();

	snail->autorelease();

	return snail;
}

Snail::Snail()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Snail_SnailWalking1);
	this->walkAnimation = Animation::create();
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking2);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking3);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking4);
	this->walkAnimation->setDelayPerUnit(0.15f);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));

	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_Enemy, true, false);

	this->addChild(this->sprite);
}

Snail::~Snail()
{
}

void Snail::update(float dt)
{
	Entity::update(dt);

	this->movement.y = 0.0f;

	/*
	if (this->getRotation() < -15.0f)
	{
		this->setRotation(-15.0f);
	}
	else if (this->getRotation() > 15.0f)
	{
		this->setRotation(15.0f);
	}*/

	if (this->movement.x < 0.0f)
	{
		this->sprite->setFlippedX(true);
	}
	else
	{
		this->sprite->setFlippedX(false);
	}
}

bool Snail::contactBegin(CollisionData data)
{
	return false;
}

bool Snail::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
		if (abs(data.normal.y) >= Entity::normalJumpThreshold)
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
			this->movement.y = 0.35f;
			break;
		}
		return true;
	}

	return false;
}

bool Snail::contactEnd(CollisionData data)
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
