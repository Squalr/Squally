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

	GameUtils::changeParent(sprite, this, true);
}

ObjectifiedTile::~ObjectifiedTile()
{
}
