#include "DarkGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DarkGrassTerrain::MapKeyTerrainType = "dark-grass";

DarkGrassTerrain* DarkGrassTerrain::create(ValueMap& properties)
{
	DarkGrassTerrain* instance = new DarkGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

DarkGrassTerrain::DarkGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		DarkGrassTerrain::MapKeyTerrainType,
		TextureResources::DarkGrassTexture,
		TerrainResources::DarkGrass_Top,
		TerrainResources::DarkGrass_TopLeft,
		TerrainResources::DarkGrass_TopRight,
		TerrainResources::DarkGrass_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::DarkGrass_Bottom,
		TerrainResources::DarkGrass_BottomLeft,
		TerrainResources::DarkGrass_BottomRight,
		TerrainResources::DarkGrass_BottomConnector,
		TerrainResources::DarkGrass_Left,
		TerrainResources::DarkGrass_LeftConnector,
		TerrainResources::DarkGrass_Right,
		TerrainResources::DarkGrass_RightConnector,
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
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

DarkGrassTerrain::~DarkGrassTerrain()
{
}
