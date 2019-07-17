#include "DarkGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DarkGrassTerrain::MapKeyTerrainTypeDarkGrass = "dark-grass";

DarkGrassTerrain* DarkGrassTerrain::create(ValueMap& initProperties)
{
	DarkGrassTerrain* instance = new DarkGrassTerrain(initProperties);

	instance->autorelease();

	return instance;
}

DarkGrassTerrain::DarkGrassTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		DarkGrassTerrain::MapKeyTerrainTypeDarkGrass,
		TerrainResources::DarkGrass_DarkGrassTexture,
		TerrainResources::DarkGrass_DarkGrass,
		TerrainResources::DarkGrass_DarkGrassTopLeft,
		TerrainResources::DarkGrass_DarkGrassTopRight,
		TerrainResources::DarkGrass_DarkGrassBottom,
		TerrainResources::DarkGrass_DarkGrassBottomLeft,
		TerrainResources::DarkGrass_DarkGrassBottomRight,
		TerrainResources::DarkGrass_DarkGrassLeft,
		TerrainResources::DarkGrass_DarkGrassRight,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

DarkGrassTerrain::~DarkGrassTerrain()
{
}
