#pragma once
#include <iomanip>
#include <sstream>
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Resources/ShaderResources.h"
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
	void buildInnerGeometry();
	void buildCollisionEdge();
	void buildInnerTextures();
	void buildInfill(Color4B infillColor);
	void buildSurfaceTextures();
	Vec2 getOutwardNormal(std::tuple<Vec2, Vec2> segment, std::vector<AlgoUtils::Triangle> triangles);
	float getSegmentAngle(std::tuple<Vec2, Vec2> segment, std::vector<AlgoUtils::Triangle> triangles);

	std::vector<Vec2> points;
	std::vector<std::tuple<Vec2, Vec2>> segments;
	std::vector<AlgoUtils::Triangle> triangles;

	std::vector<Vec2> innerPoints;
	std::vector<std::tuple<Vec2, Vec2>> innerSegments;
	std::vector<AlgoUtils::Triangle> innerTriangles;

	CollisionObject* edgeCollisionObject;
	Node* edgeCollisionNode;
	Node* innerTexturesNode;
	Node* infillNode;
	Node* topsNode;
	Node* leftWallNode;
	Node* rightWallNode;
	Node* bottomsNode;
	Node* debugNode;

	static const bool EnableTerrainDebugging;
	static const float InnerGeometryDistance;
};
