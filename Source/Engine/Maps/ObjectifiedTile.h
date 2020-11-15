#pragma once

#include "cocos/base/ccTypes.h"

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

// A special class for represeting a tile as an object to allow for dynamic z-sorting in isometric maps
class ObjectifiedTile : public GameObject
{
public:
	static ObjectifiedTile* create(cocos2d::Sprite* sprite, cocos2d::ValueMap properties);

protected:
	ObjectifiedTile(cocos2d::Sprite* sprite, cocos2d::ValueMap properties);
	virtual ~ObjectifiedTile();

private:
	typedef GameObject super;
	
	cocos2d::Sprite* innerSprite;
};
