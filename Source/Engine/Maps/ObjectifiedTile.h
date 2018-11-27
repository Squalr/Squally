#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

// A special class for represeting a tile as an object to allow for dynamic z-sorting in isometric maps
class ObjectifiedTile : public HackableObject
{
public:
	static ObjectifiedTile* create(Sprite* sprite, ValueMap* initProperties);

protected:
	ObjectifiedTile(Sprite* sprite, ValueMap* initProperties);
	~ObjectifiedTile();

private:
	Sprite * innerSprite;
};
