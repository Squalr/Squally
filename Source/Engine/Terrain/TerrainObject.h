#pragma once
#include <string>

#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/AlgoUtils.h"

namespace cocos2d
{
	class DrawNode;
	class Sprite;
}

class TextureObject;

class TerrainObject : public HackableObject
{
public:
	struct InfillData
	{
		cocos2d::Color4B infillColor;
		bool applyInfill;
		bool blurInfill;

		InfillData() : infillColor(cocos2d::Color4B::BLACK), applyInfill(false), blurInfill(false) { }
		InfillData(cocos2d::Color4B infillColor, bool applyInfill, bool blurInfill) : infillColor(infillColor), applyInfill(applyInfill), blurInfill(blurInfill) { }
	};

	struct TerrainData
	{
		std::function<TextureObject*(cocos2d::ValueMap)> textureFactory;
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
		cocos2d::Vec2 topConnectorOffset;
		cocos2d::Vec2 topConnectorConcaveOffset;
		cocos2d::Vec2 topConnectorConcaveDeepOffset;
		cocos2d::Vec2 topConnectorConvexOffset;
		cocos2d::Vec2 topConnectorConvexDeepOffset;
		cocos2d::Vec2 bottomConnectorOffset;
		InfillData infillData;
		bool buildCollision;

		TerrainData(
			std::function<TextureObject*(cocos2d::ValueMap)> textureFactory,
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
			cocos2d::Vec2 topConnectorOffset,
			cocos2d::Vec2 topConnectorConcaveOffset,
			cocos2d::Vec2 topConnectorConcaveDeepOffset,
			cocos2d::Vec2 topConnectorConvexOffset,
			cocos2d::Vec2 topConnectorConvexDeepOffset,
			cocos2d::Vec2 bottomConnectorOffset,
			InfillData infillData = InfillData(),
			bool buildCollision = true
			) :
			textureFactory(textureFactory),
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
			topConnectorOffset(topConnectorOffset),
			topConnectorConcaveOffset(topConnectorConcaveOffset),
			topConnectorConcaveDeepOffset(topConnectorConcaveDeepOffset),
			topConnectorConvexOffset(topConnectorConvexOffset),
			topConnectorConvexDeepOffset(topConnectorConvexDeepOffset),
			bottomConnectorOffset(bottomConnectorOffset),
			infillData(infillData),
			buildCollision(buildCollision)
		{
		}

		TerrainData()
		{
		}
	};

	void setDynamic(bool isDynamic);

	static const std::string MapKey;
	static const std::string PropertyTopOnly;
	static unsigned int NextTerrainId;

protected:
	TerrainObject(cocos2d::ValueMap& properties, TerrainData terrainData);
	virtual ~TerrainObject();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	cocos2d::ValueMap transformPropertiesForTexture(cocos2d::ValueMap properties);

private:
	typedef HackableObject super;

	enum class TileMethod
	{
		Horizontal,
		Vertical,
		None
	};

	void initResources();
	void setPoints(const std::vector<cocos2d::Vec2>& points);
	void cullCollision();
	void buildCollision();
	void buildInnerTextures();
	void buildInfill(InfillData infillData);
	void buildSurfaceShadow();
	void buildSurfaceTextures();
	void buildSegment(cocos2d::Node* parent, cocos2d::Sprite* sprite, cocos2d::Vec2 anchor, cocos2d::Vec2 position, float rotation, float segmentLength, TerrainObject::TileMethod tileMethod);
	void maskAgainstOther(TerrainObject* other);
	bool isTopAngle(float normalAngle);
	bool isBottomAngle(float normalAngle);
	bool isLeftAngle(float normalAngle);
	bool isRightAngle(float normalAngle);
	bool isTopCollisionFriendly(std::tuple<cocos2d::Vec2, cocos2d::Vec2>* previousSegment, std::tuple<cocos2d::Vec2, cocos2d::Vec2>* segment, std::tuple<cocos2d::Vec2, cocos2d::Vec2>* nextSegment);
	void buildTerrain();
	void updateCachedCoords(bool force = false);
	void optimizationHideOffscreenTerrain();

	TerrainData terrainData;
	bool isTopOnlyCollision = false;
	bool isInactive = false;
	bool isFlipped = false;
	bool hasBuiltTerrain = false;
	bool isDynamic = false;
	unsigned int terrainObjectId = 0;

	cocos2d::CRect drawRect;
	cocos2d::CRect boundsRect;
	cocos2d::Vec3 cachedCoords;
	std::vector<cocos2d::Vec2> points;
	std::vector<cocos2d::Vec2> intersectionPoints;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segments;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> collisionSegments;
	std::vector<AlgoUtils::Triangle> textureTriangles;
	std::vector<AlgoUtils::Triangle> infillTriangles;

	cocos2d::Node* rootNode = nullptr;
	cocos2d::Node* collisionNode = nullptr;
	cocos2d::Node* infillTexturesNode = nullptr;
	cocos2d::Node* infillNode = nullptr;
	cocos2d::Node* shadowsNode = nullptr;
	cocos2d::Node* leftWallNode = nullptr;
	cocos2d::Node* rightWallNode = nullptr;
	cocos2d::Node* bottomsNode = nullptr;
	cocos2d::Node* bottomCornersNode = nullptr;
	cocos2d::Node* topsNode = nullptr;
	cocos2d::Node* connectorsNode = nullptr;
	cocos2d::Node* topCornersNode = nullptr;
	cocos2d::DrawNode* debugDrawNode = nullptr;
	cocos2d::Node* debugLabelsNode = nullptr;

	static const float ShadowDistance;
	static const float InfillDistance;
	static const float TopThreshold;
	static const float BottomThreshold;
};
