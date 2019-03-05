#pragma once
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/AlgoUtils.h"

class TerrainObject : public HackableObject
{
public:
	struct TerrainData
	{
		float friction;
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
		cocos2d::Color4B infillColor;

		TerrainData(
			float friction,
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
			cocos2d::Color4B infillColor) :
			friction(friction),
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

	static TerrainObject* deserialize(cocos2d::ValueMap& initProperties, TerrainData terrainData);

	void setPoints(std::vector<cocos2d::Vec2> points);
	void rebuildTerrain();

	static std::string MapKeyTypeTexture;
	static std::string MapKeyTypeTerrain;
	static std::string MapKeyCollisionDisabled;

private:
	typedef HackableObject super;
	TerrainObject(cocos2d::ValueMap& initProperties, TerrainData terrainData);
	virtual ~TerrainObject();

	void onEnter() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void initializeListeners() override;
	void buildCollision();
	void buildInnerTextures();
	void buildInfill(cocos2d::Color4B infillColor);
	void buildSurfaceShadow();
	void buildSurfaceTextures();
	bool isTopAngle(float normalAngle);
	bool isBottomAngle(float normalAngle);
	bool isLeftAngle(float normalAngle);
	bool isRightAngle(float normalAngle);

	TerrainData terrainData;

	std::vector<cocos2d::Vec2> points;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segments;
	std::vector<AlgoUtils::Triangle> triangles;

	cocos2d::Node* collisionNode;
	cocos2d::Node* infillTexturesNode;
	cocos2d::Node* infillNode;
	cocos2d::Node* shadowsNode;
	cocos2d::Node* leftWallNode;
	cocos2d::Node* rightWallNode;
	cocos2d::Node* bottomsNode;
	cocos2d::Node* bottomCornersNode;
	cocos2d::Node* topsNode;
	cocos2d::Node* topCornersNode;
	cocos2d::Node* debugNode;

	static const float ShadowDistance;
	static const float InfillDistance;
	static const float TopThreshold;
	static const float BottomThreshold;
};
