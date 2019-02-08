#pragma once
#include "Engine/Maps/SerializableObject.h"

namespace cocos2d
{
	class Sprite;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

// A special class for represeting a tile as an object to allow for dynamic z-sorting in isometric maps
class ObjectifiedTile : public SerializableObject
{
public:
	static ObjectifiedTile* create(cocos2d::Sprite* sprite, cocos2d::ValueMap initProperties);

protected:
	ObjectifiedTile(cocos2d::Sprite* sprite, cocos2d::ValueMap initProperties);
	virtual ~ObjectifiedTile();

private:
	cocos2d::Sprite * innerSprite;
};
