#include "MarbleDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string MarbleDarkTerrain::MapKeyTerrainTypeMarbleDark = "marble-dark";

MarbleDarkTerrain* MarbleDarkTerrain::create(ValueMap& properties)
{
	MarbleDarkTerrain* instance = new MarbleDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleDarkTerrain::MarbleDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		MarbleDarkTerrain::MapKeyTerrainTypeMarbleDark,
		TerrainResources::MarbleDark_MarbleDarkTexture,
		TerrainResources::MarbleDark_MarbleDark,
		TerrainResources::MarbleDark_MarbleDarkTopLeft,
		TerrainResources::MarbleDark_MarbleDarkTopRight,
		TerrainResources::MarbleDark_MarbleDarkBottom,
		TerrainResources::MarbleDark_MarbleDarkBottomLeft,
		TerrainResources::MarbleDark_MarbleDarkBottomRight,
		TerrainResources::MarbleDark_MarbleDarkLeft,
		TerrainResources::MarbleDark_MarbleDarkRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

MarbleDarkTerrain::~MarbleDarkTerrain()
{
}
