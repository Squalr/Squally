#include "ShipAltTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string ShipAltTerrain::MapKeyTerrainTypeShipAlt = "ship-alt";

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
		ShipAltTerrain::MapKeyTerrainTypeShipAlt,
		TerrainResources::ShipAlt_ShipAltTexture,
		TerrainResources::ShipAlt_ShipAlt,
		TerrainResources::ShipAlt_ShipAltTopLeft,
		TerrainResources::ShipAlt_ShipAltTopRight,
		TerrainResources::ShipAlt_ShipAltBottom,
		TerrainResources::ShipAlt_ShipAltBottomLeft,
		TerrainResources::ShipAlt_ShipAltBottomRight,
		TerrainResources::ShipAlt_ShipAltLeft,
		TerrainResources::ShipAlt_ShipAltRight,
		cocos2d::Vec2(0.0f, -16.0f),
		cocos2d::Vec2(-22.0f, 0.0f),
		cocos2d::Vec2(22.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

ShipAltTerrain::~ShipAltTerrain()
{
}
