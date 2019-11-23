#include "ShipTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipTerrain::MapKeyTerrainType = "ship";

ShipTerrain* ShipTerrain::create(ValueMap& properties)
{
	ShipTerrain* instance = new ShipTerrain(properties);

	instance->autorelease();

	return instance;
}

ShipTerrain::ShipTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		ShipTerrain::MapKeyTerrainType,
		TextureResources::ShipTexture,
		TerrainResources::Ship_Top,
		TerrainResources::Ship_TopLeft,
		TerrainResources::Ship_TopRight,
		TerrainResources::Ship_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Ship_Bottom,
		TerrainResources::Ship_BottomLeft,
		TerrainResources::Ship_BottomRight,
		TerrainResources::Ship_BottomConnector,
		TerrainResources::Ship_Left,
		TerrainResources::Ship_LeftConnector,
		TerrainResources::Ship_Right,
		TerrainResources::Ship_RightConnector,
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
		Color4B(11, 30, 39, 255)))
{
}

ShipTerrain::~ShipTerrain()
{
}
