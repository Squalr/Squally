#pragma once
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class GridObject : public SmartNode
{
public:
	static GridObject* create(cocos2d::Node* inner, cocos2d::Vec2 spawnCoords, bool isObjectStatic);

	void setCoords(cocos2d::Vec2 coords);
	cocos2d::Vec2 getCoords();
	cocos2d::Vec2 getSpawnCoords();

private:
	GridObject(cocos2d::Node* inner, cocos2d::Vec2 spawnCoords, bool isObjectStatic);
	~GridObject();

	void onEnter() override;

	cocos2d::Vec2 initCoords;
	cocos2d::Vec2 gridCoords;

	bool isStatic;
};
