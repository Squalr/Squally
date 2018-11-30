#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MPE_fastpoly2tri.h"
#include "Resources/TerrainResources.h"

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
	void buildTops();
	void buildLeftWall();
	void buildRightWall();
	void buildBottoms();

	std::vector<Vec2> points;
	std::vector<std::tuple<Vec2, Vec2>> segments;
	Node* collisionNode;
	Node* infillNode;
	Node* topsNode;
	Node* leftWallNode;
	Node* rightWallNode;
	Node* bottomsNode;
};
