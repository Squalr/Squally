#include "ShadeGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string ShadeGrassTerrain::MapKeyTerrainTypeShadeGrass = "shade-grass";

ShadeGrassTerrain* ShadeGrassTerrain::create(ValueMap& initProperties)
{
	ShadeGrassTerrain* instance = new ShadeGrassTerrain(initProperties);

	instance->autorelease();

	return instance;
}

ShadeGrassTerrain::ShadeGrassTerrain(ValueMap& initProperties) : super(
	initProperties,
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
		Color4B(11, 30, 39, 255)))
{
}

ShadeGrassTerrain::~ShadeGrassTerrain()
{
}
