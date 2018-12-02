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
	void buildCollisionEdge();
	void buildInnerTextures();
	void buildInfill(Color4B infillColor);
	void buildSurfaceShadow();
	void buildSurfaceTextures();

	std::vector<Vec2> points;
	std::vector<std::tuple<Vec2, Vec2>> segments;
	std::vector<AlgoUtils::Triangle> triangles;

	CollisionObject* edgeCollisionObject;
	Node* edgeCollisionNode;
	Node* infillTexturesNode;
	Node* infillNode;
	Node* shadowsNode;
	Node* topsNode;
	Node* leftWallNode;
	Node* rightWallNode;
	Node* bottomsNode;
	Node* debugNode;

	static const bool EnableTerrainDebugging;
	static const float ShadowDistance;
	static const float InfillDistance;
};
