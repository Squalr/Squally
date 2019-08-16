#include "TrailTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string TrailTerrain::MapKeyTerrainTypeTrail = "trail";

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
		TrailTerrain::MapKeyTerrainTypeTrail,
		TerrainResources::Trail_TrailTexture,
		TerrainResources::Trail_Trail,
		TerrainResources::Trail_TrailTopLeft,
		TerrainResources::Trail_TrailTopRight,
		TerrainResources::Trail_TrailBottom,
		TerrainResources::Trail_TrailBottomLeft,
		TerrainResources::Trail_TrailBottomRight,
		TerrainResources::Trail_TrailLeft,
		TerrainResources::Trail_TrailRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

TrailTerrain::~TrailTerrain()
{
}
