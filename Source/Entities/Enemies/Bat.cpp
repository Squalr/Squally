#include "Bat.h"

Bat* Bat::create()
{
	Bat* bat = new Bat();

	bat->autorelease();

	return bat;
}

Bat::Bat() : Entity::Entity()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 4000.0f;

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Bat_Fly1);
	this->walkAnimation = Animation::create();
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Bat_Fly1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Bat_Fly2);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Bat_Fly3);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Bat_Fly4);
	this->walkAnimation->setDelayPerUnit(0.1f);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));

	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_EnemyFlying, true, false);

	this->addChild(this->sprite);
}

Bat::~Bat()
{
}

void Bat::update(float dt)
{
	Entity::update(dt);

	this->movement.y = 0.0f;

	if (this->movement.x < 0.0f)
	{
		this->sprite->setFlippedX(true);
	}
	else
	{
		this->sprite->setFlippedX(false);
	}
}

bool Bat::contactBegin(CollisionData data)
{
	return false;
}

bool Bat::contactUpdate(CollisionData data)
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

bool Bat::contactEnd(CollisionData data)
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
