#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class GridObject : public Node
{
public:
	static GridObject* create(Node* inner, Vec2 spawnCoords, bool isObjectStatic);

	void setCoords(Vec2 coords);
	Vec2 getCoords();
	Vec2 getSpawnCoords();

private:
	GridObject(Node* inner, Vec2 spawnCoords, bool isObjectStatic);
	~GridObject();

	void onEnter() override;

	Vec2 initCoords;
	Vec2 gridCoords;

	bool isStatic;
};
