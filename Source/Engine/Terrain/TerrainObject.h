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
#include "Engine/Utils/RenderUtils.h"
#include "Resources/ShaderResources.h"

using namespace cocos2d;

class TerrainObject : public HackableObject
{
public:
	struct TerrainData
	{
		std::string textureMapKeyValue;
		std::string textureResource;
		std::string topResource;
		std::string topCornerLeftResource;
		std::string topCornerRightResource;
		std::string bottomResource;
		std::string bottomCornerLeftResource;
		std::string bottomCornerRightResource;
		std::string leftResource;
		std::string rightResource;
		Color4B infillColor;

		TerrainData(
			std::string textureMapKeyValue,
			std::string textureResource,
			std::string topResource,
			std::string topCornerLeftResource,
			std::string topCornerRightResource,
			std::string bottomResource,
			std::string bottomCornerLeftResource,
			std::string bottomCornerRightResource,
			std::string leftResource,
			std::string rightResource,
			Color4B infillColor) :
			textureMapKeyValue(textureMapKeyValue),
			textureResource(textureResource),
			topResource(topResource),
			topCornerLeftResource(topCornerLeftResource),
			topCornerRightResource(topCornerRightResource),
			bottomResource(bottomResource),
			bottomCornerLeftResource(bottomCornerLeftResource),
			bottomCornerRightResource(bottomCornerRightResource),
			leftResource(leftResource),
			rightResource(rightResource),
			infillColor(infillColor)
		{
		}

		TerrainData()
		{
		}
	};

	static TerrainObject* deserialize(ValueMap* initProperties, TerrainData terrainData);

	void setPoints(std::vector<Vec2> points);
	void rebuildTerrain();

	static std::string MapKeyTypeTexture;
	static std::string MapKeyTypeTerrain;

private:
	TerrainObject(ValueMap* initProperties, TerrainData terrainData);
	~TerrainObject();

	void onEnter() override;
	void initializeListeners() override;
	void buildCollision();
	void buildInnerTextures();
	void buildInfill(Color4B infillColor);
	void buildSurfaceShadow();
	void buildSurfaceTextures();

	TerrainData terrainData;

	std::vector<Vec2> points;
	std::vector<std::tuple<Vec2, Vec2>> segments;
	std::vector<AlgoUtils::Triangle> triangles;

	Node* collisionNode;
	Node* infillTexturesNode;
	Node* infillNode;
	Node* shadowsNode;
	Node* leftWallNode;
	Node* rightWallNode;
	Node* bottomsNode;
	Node* topsNode;
	Node* debugNode;

	static const bool EnableTerrainDebugging;
	static const float ShadowDistance;
	static const float InfillDistance;
	static const float TopThreshold;
	static const float BottomThreshold;
};
