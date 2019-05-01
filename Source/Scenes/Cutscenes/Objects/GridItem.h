#pragma once
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class GridItem : public SmartNode
{
public:
	static GridItem* create(cocos2d::Node* inner, cocos2d::Vec2 spawnCoords, bool isObjectStatic);

	void setCoords(cocos2d::Vec2 coords);
	cocos2d::Vec2 getCoords();
	cocos2d::Vec2 getSpawnCoords();

private:
	GridItem(cocos2d::Node* inner, cocos2d::Vec2 spawnCoords, bool isObjectStatic);
	~GridItem();

	void onEnter() override;

	cocos2d::Vec2 initCoords;
	cocos2d::Vec2 gridCoords;

	bool isStatic;
};
