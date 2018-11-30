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

	struct ShardedTriangle
	{
		Vec2 coords[3];

		ShardedTriangle(Vec2 coordA, Vec2 coordB, Vec2 coordC)
		{
			coords[0] = coordA;
			coords[1] = coordB;
			coords[2] = coordC;
		}
	};

	void onEnter() override;
	void initializeListeners() override;
	void shardPolygon();
	void buildCollisionEdge();
	void buildInfill(Color4B infillColor);
	void buildTextures();
	Vec2 getOutwardNormal(std::tuple<Vec2, Vec2> segment);
	float getSegmentAngle(std::tuple<Vec2, Vec2> segment);
	bool isPointInShard(ShardedTriangle triangle, Vec2 point);

	std::vector<Vec2> points;
	std::vector<std::tuple<Vec2, Vec2>> segments;
	std::vector<ShardedTriangle> triangles;

	CollisionObject* edgeCollisionObject;
	Node* edgeCollisionNode;
	Node* infillNode;
	Node* topsNode;
	Node* leftWallNode;
	Node* rightWallNode;
	Node* bottomsNode;
	Node* debugNode;

	static const bool EnableTerrainDebugging;
};
