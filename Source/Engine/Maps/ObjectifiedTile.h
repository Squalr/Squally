#pragma once
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

// A special class for represeting a tile as an object to allow for dynamic z-sorting in isometric maps
class ObjectifiedTile : public GameObject
{
public:
	static ObjectifiedTile* create(cocos2d::Sprite* sprite, cocos2d::ValueMap properties);

protected:
	ObjectifiedTile(cocos2d::Sprite* sprite, cocos2d::ValueMap properties);
	~ObjectifiedTile();

private:
	cocos2d::Sprite* innerSprite;
};
