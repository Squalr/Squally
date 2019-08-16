#include "ShadeGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string ShadeGrassTerrain::MapKeyTerrainTypeShadeGrass = "shade-grass";

ShadeGrassTerrain* ShadeGrassTerrain::create(ValueMap& properties)
{
	ShadeGrassTerrain* instance = new ShadeGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

ShadeGrassTerrain::ShadeGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		ShadeGrassTerrain::MapKeyTerrainTypeShadeGrass,
		TerrainResources::ShadeGrass_ShadeGrassTexture,
		TerrainResources::ShadeGrass_ShadeGrass,
		TerrainResources::ShadeGrass_ShadeGrassTopLeft,
		TerrainResources::ShadeGrass_ShadeGrassTopRight,
		TerrainResources::ShadeGrass_ShadeGrassBottom,
		TerrainResources::ShadeGrass_ShadeGrassBottomLeft,
		TerrainResources::ShadeGrass_ShadeGrassBottomRight,
		TerrainResources::ShadeGrass_ShadeGrassLeft,
		TerrainResources::ShadeGrass_ShadeGrassRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, -12.0f),
		cocos2d::Vec2(16.0f, -12.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

ShadeGrassTerrain::~ShadeGrassTerrain()
{
}
