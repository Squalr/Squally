#include "WoodTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string WoodTerrain::MapKeyTerrainTypeWood = "wood";

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
		WoodTerrain::MapKeyTerrainTypeWood,
		TerrainResources::Wood_WoodTexture,
		TerrainResources::Wood_Wood,
		TerrainResources::Wood_WoodTopLeft,
		TerrainResources::Wood_WoodTopRight,
		TerrainResources::Wood_WoodBottom,
		TerrainResources::Wood_WoodBottomLeft,
		TerrainResources::Wood_WoodBottomRight,
		TerrainResources::Wood_WoodLeft,
		TerrainResources::Wood_WoodRight,
		cocos2d::Vec2(0.0f, -42.0f),
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

WoodTerrain::~WoodTerrain()
{
}
