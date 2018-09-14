#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

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
