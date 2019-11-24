#include "TrailTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TrailTerrain::MapKeyTerrainType = "trail";

TrailTerrain* TrailTerrain::create(ValueMap& properties)
{
	TrailTerrain* instance = new TrailTerrain(properties);

	instance->autorelease();

	return instance;
}

TrailTerrain::TrailTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		TrailTerrain::MapKeyTerrainType,
		TextureResources::TrailTexture,
		TerrainResources::Trail_Top,
		TerrainResources::Trail_TopLeft,
		TerrainResources::Trail_TopRight,
		TerrainResources::Trail_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Trail_Bottom,
		TerrainResources::Trail_BottomLeft,
		TerrainResources::Trail_BottomRight,
		TerrainResources::Trail_BottomConnector,
		TerrainResources::Trail_Left,
		TerrainResources::Trail_LeftConnector,
		TerrainResources::Trail_Right,
		TerrainResources::Trail_RightConnector,
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

TrailTerrain::~TrailTerrain()
{
}
