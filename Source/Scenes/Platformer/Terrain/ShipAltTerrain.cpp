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
		TerrainResources::ShipAlt_ShipAlt,
		TerrainResources::ShipAlt_ShipAltTopLeft,
		TerrainResources::ShipAlt_ShipAltTopRight,
		TerrainResources::ShipAlt_ShipAltBottom,
		TerrainResources::ShipAlt_ShipAltBottomLeft,
		TerrainResources::ShipAlt_ShipAltBottomRight,
		TerrainResources::ShipAlt_ShipAltLeft,
		TerrainResources::ShipAlt_ShipAltRight,
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

ShipAltTerrain::~ShipAltTerrain()
{
}
