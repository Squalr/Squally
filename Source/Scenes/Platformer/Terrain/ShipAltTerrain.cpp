#include "ShipAltTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipAltTerrain::MapKeyTerrainType = "ship-alt";

ShipAltTerrain* ShipAltTerrain::create(ValueMap& properties)
{
	ShipAltTerrain* instance = new ShipAltTerrain(properties);

	instance->autorelease();

	return instance;
}

ShipAltTerrain::ShipAltTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		ShipAltTerrain::MapKeyTerrainType,
		TextureResources::ShipAltTexture,
		TerrainResources::ShipAlt_Top,
		TerrainResources::ShipAlt_TopLeft,
		TerrainResources::ShipAlt_TopRight,
		TerrainResources::ShipAlt_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::ShipAlt_Bottom,
		TerrainResources::ShipAlt_BottomLeft,
		TerrainResources::ShipAlt_BottomRight,
		TerrainResources::ShipAlt_BottomConnector,
		TerrainResources::ShipAlt_Left,
		TerrainResources::ShipAlt_LeftConnector,
		TerrainResources::ShipAlt_Right,
		TerrainResources::ShipAlt_RightConnector,
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

ShipAltTerrain::~ShipAltTerrain()
{
}
