#include "Poly.h"

Poly* Poly::create()
{
	Poly* poly = new Poly();

	poly->autorelease();

	return poly;
}

Poly::Poly()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Poly_idle_1);
	this->walkAnimation = Animation::create();
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Poly_idle_1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Poly_idle_1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Poly_idle_1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Poly_idle_1);
	this->walkAnimation->setDelayPerUnit(0.15f);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));

	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_Enemy, true, false);

	this->addChild(this->sprite);
}

Poly::~Poly()
{
}

void Poly::update(float dt)
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

bool Poly::contactBegin(CollisionData data)
{
	return false;
}

bool Poly::contactUpdate(CollisionData data)
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

bool Poly::contactEnd(CollisionData data)
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
