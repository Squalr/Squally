#pragma once
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/AlgoUtils.h"

namespace cocos2d
{
	class Sprite;
}

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
		std::string topConnectorResource;
		std::string topConnectorConcaveResource;
		std::string topConnectorConcaveDeepResource;
		std::string topConnectorConvexResource;
		std::string topConnectorConvexDeepResource;
		std::string bottomResource;
		std::string bottomCornerLeftResource;
		std::string bottomCornerRightResource;
		std::string bottomConnectorResource;
		std::string leftResource;
		std::string leftConnectorResource;
		std::string rightResource;
		std::string rightConnectorResource;
		cocos2d::Vec2 topOffset;
		cocos2d::Vec2 bottomOffset;
		cocos2d::Vec2 leftOffset;
		cocos2d::Vec2 rightOffset;
		cocos2d::Vec2 topLeftCornerOffset;
		cocos2d::Vec2 topRightCornerOffset;
		cocos2d::Vec2 bottomLeftCornerOffset;
		cocos2d::Vec2 bottomRightCornerOffset;
		cocos2d::Color4B infillColor;

		TerrainData(
			float friction,
			std::string textureMapKeyValue,
			std::string textureResource,
			std::string topResource,
			std::string topCornerLeftResource,
			std::string topCornerRightResource,
			std::string topConnectorResource,
			std::string topConnectorConcaveResource,
			std::string topConnectorConcaveDeepResource,
			std::string topConnectorConvexResource,
			std::string topConnectorConvexDeepResource,
			std::string bottomResource,
			std::string bottomCornerLeftResource,
			std::string bottomCornerRightResource,
			std::string bottomConnectorResource,
			std::string leftResource,
			std::string leftConnectorResource,
			std::string rightResource,
			std::string rightConnectorResource,
			cocos2d::Vec2 topOffset,
			cocos2d::Vec2 bottomOffset,
			cocos2d::Vec2 leftOffset,
			cocos2d::Vec2 rightOffset,
			cocos2d::Vec2 topLeftCornerOffset,
			cocos2d::Vec2 topRightCornerOffset,
			cocos2d::Vec2 bottomLeftCornerOffset,
			cocos2d::Vec2 bottomRightCornerOffset,
			cocos2d::Color4B infillColor) :
			friction(friction),
			textureMapKeyValue(textureMapKeyValue),
			textureResource(textureResource),
			topResource(topResource),
			topCornerLeftResource(topCornerLeftResource),
			topCornerRightResource(topCornerRightResource),
			topConnectorResource(topConnectorResource),
			topConnectorConcaveResource(topConnectorConcaveResource),
			topConnectorConcaveDeepResource(topConnectorConcaveDeepResource),
			topConnectorConvexResource(topConnectorConvexResource),
			topConnectorConvexDeepResource(topConnectorConvexDeepResource),
			bottomResource(bottomResource),
			bottomCornerLeftResource(bottomCornerLeftResource),
			bottomCornerRightResource(bottomCornerRightResource),
			bottomConnectorResource(bottomConnectorResource),
			leftResource(leftResource),
			leftConnectorResource(leftConnectorResource),
			rightResource(rightResource),
			rightConnectorResource(rightConnectorResource),
			topOffset(topOffset),
			bottomOffset(bottomOffset),
			leftOffset(leftOffset),
			rightOffset(rightOffset),
			topLeftCornerOffset(topLeftCornerOffset),
			topRightCornerOffset(topRightCornerOffset),
			bottomLeftCornerOffset(bottomLeftCornerOffset),
			bottomRightCornerOffset(bottomRightCornerOffset),
			infillColor(infillColor)
		{
		}

		TerrainData()
		{
		}
	};

	static std::string MapKeyTypeIsHollow;
	static std::string MapKeyTypeTerrain;

protected:
	TerrainObject(cocos2d::ValueMap& properties, TerrainData terrainData);
	~TerrainObject();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	enum class TileMethod
	{
		Horizontal,
		Vertical,
		None
	};

	void setPoints(std::vector<cocos2d::Vec2> points);
	void rebuildTerrain(TerrainData terrainData);
	void removeHollowEdgeCollisions();
	void buildCollision();
	void buildInnerTextures();
	void buildInfill(cocos2d::Color4B infillColor);
	void buildSurfaceShadow();
	void buildSurfaceTextures();
	void buildSegment(cocos2d::Node* parent, cocos2d::Sprite* sprite, cocos2d::Vec2 anchor, cocos2d::Vec2 position, float rotation, float segmentLength, TerrainObject::TileMethod tileMethod);
	void maskAgainstOther(TerrainObject* other);
	bool isTopAngle(float normalAngle);
	bool isBottomAngle(float normalAngle);
	bool isLeftAngle(float normalAngle);
	bool isRightAngle(float normalAngle);

	TerrainData terrainData;
	bool isHollow;
	bool isInactive;
	bool isFlipped;

	cocos2d::Rect boundsRect;
	std::vector<cocos2d::Vec2> points;
	std::vector<cocos2d::Vec2> intersectionPoints;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segments;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> collisionSegments;
	std::vector<AlgoUtils::Triangle> textureTriangles;
	std::vector<AlgoUtils::Triangle> infillTriangles;

	cocos2d::Node* collisionNode;
	cocos2d::Node* infillTexturesNode;
	cocos2d::Node* infillNode;
	cocos2d::Node* shadowsNode;
	cocos2d::Node* leftWallNode;
	cocos2d::Node* rightWallNode;
	cocos2d::Node* bottomsNode;
	cocos2d::Node* bottomCornersNode;
	cocos2d::Node* topsNode;
	cocos2d::Node* connectorsNode;
	cocos2d::Node* topCornersNode;
	cocos2d::Node* debugNode;

	static const float ShadowDistance;
	static const float InfillDistance;
	static const float HollowDistance;
	static const float TopThreshold;
	static const float BottomThreshold;
};
