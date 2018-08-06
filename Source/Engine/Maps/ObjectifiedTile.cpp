#include "ObjectifiedTile.h"

ObjectifiedTile* ObjectifiedTile::create(Sprite* sprite, ValueMap* initProperties)
{
	ObjectifiedTile* instance = new ObjectifiedTile(sprite, initProperties);

	instance->autorelease();

	return instance;
}

ObjectifiedTile::ObjectifiedTile(Sprite* sprite, ValueMap* initProperties) : HackableObject(initProperties)
{
	this->innerSprite = sprite;

	// Transfer position from sprite to this object
	Vec2 spritePosition = sprite->getPosition();
	this->setPosition(spritePosition);
	sprite->setPosition(Vec2::ZERO);

	GameUtils::changeParent(sprite, this, false);
}

ObjectifiedTile::~ObjectifiedTile()
{
}
