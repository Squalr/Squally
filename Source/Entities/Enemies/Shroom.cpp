#include "Shroom.h"

Shroom* Shroom::create()
{
	Shroom* shroom = new Shroom();

	shroom->autorelease();

	return shroom;
}

Shroom::Shroom()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 4000.0f;

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Shroom_ShroomWalking1);
	this->walkAnimation = Animation::create();
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Shroom_ShroomWalking1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Shroom_ShroomWalking2);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Shroom_ShroomWalking3);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Shroom_ShroomWalking4);
	this->walkAnimation->setDelayPerUnit(0.1f);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));

	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_Enemy, true, false);

	this->addChild(this->sprite);
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
			this->movement.y = 0.5f;
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
