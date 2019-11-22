#include "TrailTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TrailTerrain::MapKeyTerrainType = "trail";

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
		TrailTerrain::MapKeyTerrainType,
		TextureResources::TrailTexture,
		TerrainResources::Trail_Trail,
		TerrainResources::Trail_TrailTopLeft,
		TerrainResources::Trail_TrailTopRight,
		TerrainResources::Trail_TrailBottom,
		TerrainResources::Trail_TrailBottomLeft,
		TerrainResources::Trail_TrailBottomRight,
		TerrainResources::Trail_TrailLeft,
		TerrainResources::Trail_TrailRight,
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

TrailTerrain::~TrailTerrain()
{
}
