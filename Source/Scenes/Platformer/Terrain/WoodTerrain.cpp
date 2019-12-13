#include "WoodTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string WoodTerrain::MapKeyTerrainType = "wood";

WoodTerrain* WoodTerrain::create(ValueMap& properties)
{
	WoodTerrain* instance = new WoodTerrain(properties);

	instance->autorelease();

	return instance;
}

WoodTerrain::WoodTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		WoodTerrain::MapKeyTerrainType,
		TextureResources::WoodTexture,
		TerrainResources::Wood_Top,
		TerrainResources::Wood_TopLeft,
		TerrainResources::Wood_TopRight,
		TerrainResources::Wood_TopConnector,
		TerrainResources::Wood_TopConnectorConcave,
		TerrainResources::Wood_TopConnectorConcaveDeep,
		TerrainResources::Wood_TopConnectorConvex,
		TerrainResources::Wood_TopConnectorConvexDeep,
		TerrainResources::Wood_Bottom,
		TerrainResources::Wood_BottomLeft,
		TerrainResources::Wood_BottomRight,
		TerrainResources::Wood_BottomConnector,
		TerrainResources::Wood_Left,
		TerrainResources::Wood_LeftConnector,
		TerrainResources::Wood_Right,
		TerrainResources::Wood_RightConnector,
		// Top
		Vec2(0.0f, -42.0f),
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2::ZERO,
		// TopRight
		Vec2::ZERO,
		// BottomLeft
		Vec2::ZERO,
		// BottomRight
		Vec2::ZERO,
		// TopConnector
		Vec2::ZERO,
		// TopConnectorConcave
		Vec2(0.0f, 4.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 6.0f),
		// TopConnectorConvex
		Vec2(0.0f, -2.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -14.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

WoodTerrain::~WoodTerrain()
{
}
