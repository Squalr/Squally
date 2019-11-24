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
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Wood_Bottom,
		TerrainResources::Wood_BottomLeft,
		TerrainResources::Wood_BottomRight,
		TerrainResources::Wood_BottomConnector,
		TerrainResources::Wood_Left,
		TerrainResources::Wood_LeftConnector,
		TerrainResources::Wood_Right,
		TerrainResources::Wood_RightConnector,
		// Top
		Vec2::ZERO,
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
		Vec2::ZERO,
		// TopConnectorConcaveDeep
		Vec2::ZERO,
		// TopConnectorConvex
		Vec2::ZERO,
		// TopConnectorConvexDeep
		Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

WoodTerrain::~WoodTerrain()
{
}
