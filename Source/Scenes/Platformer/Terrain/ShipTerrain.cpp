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
		cocos2d::Vec2(0.0f, -16.0f),
		cocos2d::Vec2(-56.0f, 0.0f),
		cocos2d::Vec2(56.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

ShipTerrain::~ShipTerrain()
{
}
