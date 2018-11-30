#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MPE_fastpoly2tri.h"

using namespace cocos2d;

class TerrainObject : public HackableObject
{
public:
	static TerrainObject* deserialize(ValueMap* initProperties);

	void setPoints(std::vector<Vec2> points);
	void rebuildTerrain();

	static std::string MapKeyTypeTerrain;

private:
	TerrainObject(ValueMap* initProperties);
	~TerrainObject();

	void onEnter() override;
	void initializeListeners() override;
	void buildCollisionBounds();
	void buildInfill(Color4B infillColor);

	std::vector<Vec2> points;
	Node* collisionNode;
	Node* infillNode;
};
