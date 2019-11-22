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
		TerrainResources::Ship_Ship,
		TerrainResources::Ship_ShipTopLeft,
		TerrainResources::Ship_ShipTopRight,
		TerrainResources::Ship_ShipBottom,
		TerrainResources::Ship_ShipBottomLeft,
		TerrainResources::Ship_ShipBottomRight,
		TerrainResources::Ship_ShipLeft,
		TerrainResources::Ship_ShipRight,
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
