#include "Knight.h"

Knight* Knight::create()
{
	Knight* knight = new Knight();

	knight->autorelease();

	return knight;
}

Knight::Knight() : Entity::Entity()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->spriteNode = Node::create();
	this->knightSprite = Sprite::create(Resources::Ingame_Sprites_Knight_KnightStanding);

	this->init(PhysicsBody::createBox(this->knightSprite->getContentSize()), CategoryGroup::G_Npc, true, false);

	this->spriteNode->addChild(this->knightSprite);
	this->addChild(this->spriteNode);
}

Knight::~Knight()
{
}

void Knight::update(float dt)
{
	Entity::update(dt);

	this->movement.y = 0.0f;

	if (this->movement.x < 0.0f)
	{
		this->knightSprite->setFlippedX(true);
	}
	else
	{
		this->knightSprite->setFlippedX(false);
	}
}

bool Knight::contactBegin(CollisionData data)
{
	return false;
}

bool Knight::contactUpdate(CollisionData data)
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
			break;
		case CollisionDirection::Right:
			break;
		case CollisionDirection::StepLeft:
		case CollisionDirection::StepRight:
			break;
		}
		return true;
	}

	return false;
}

bool Knight::contactEnd(CollisionData data)
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
