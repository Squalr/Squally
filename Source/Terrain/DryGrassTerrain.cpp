#include "DryGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryGrassTerrain::MapKeyTerrainTypeDryGrass = "dry-grass";

DryGrassTerrain* DryGrassTerrain::create(ValueMap& initProperties)
{
	DryGrassTerrain* instance = new DryGrassTerrain(initProperties);

	instance->autorelease();

	return instance;
}

DryGrassTerrain::DryGrassTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		DryGrassTerrain::MapKeyTerrainTypeDryGrass,
		TerrainResources::DryGrass_DryGrassTexture,
		TerrainResources::DryGrass_DryGrass,
		TerrainResources::DryGrass_DryGrassTopLeft,
		TerrainResources::DryGrass_DryGrassTopRight,
		TerrainResources::DryGrass_DryGrassBottom,
		TerrainResources::DryGrass_DryGrassBottomLeft,
		TerrainResources::DryGrass_DryGrassBottomRight,
		TerrainResources::DryGrass_DryGrassLeft,
		TerrainResources::DryGrass_DryGrassRight,
		Color4B(11, 30, 39, 255)))
{
}

DryGrassTerrain::~DryGrassTerrain()
{
}
