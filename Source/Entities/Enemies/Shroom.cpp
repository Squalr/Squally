#include "Shroom.h"

Shroom* Shroom::create()
{
	Shroom* player = new Shroom();

	player->autorelease();

	return player;
}

Shroom::Shroom()
{
	this->sprite = Sprite::create(Resources::Ingame_Sprites_Shroom_ShroomWalking1);
	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_Enemy, true);
	this->addChild(this->sprite);
}

Shroom::~Shroom()
{
}

void Shroom::update(float dt)
{
	Entity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;
}

bool Shroom::contactBegin(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		if (data.normal.y < Shroom::normalJumpThreshold)
		{
			this->isOnGround = true;
		}
		return true;
	case CategoryGroup::G_Force:
		return true;
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		return false;
	}

	return false;
}

bool Shroom::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		if (data.normal.y < Shroom::normalJumpThreshold)
		{
			this->isOnGround = true;
		}
		return true;
	case CategoryGroup::G_Force:
		return true;
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		return false;
	}

	return false;
}

bool Shroom::contactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		this->isOnGround = false;
		return true;
	case CategoryGroup::G_Force:
		return true;
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		return false;
	}

	return false;
}
