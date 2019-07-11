#include "MarbleGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string MarbleGrassTerrain::MapKeyTerrainTypeMarbleGrass = "marble-grass";

MarbleGrassTerrain* MarbleGrassTerrain::create(ValueMap& initProperties)
{
	MarbleGrassTerrain* instance = new MarbleGrassTerrain(initProperties);

	instance->autorelease();

	return instance;
}

MarbleGrassTerrain::MarbleGrassTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		MarbleGrassTerrain::MapKeyTerrainTypeMarbleGrass,
		TerrainResources::MarbleGrass_MarbleGrassTexture,
		TerrainResources::MarbleGrass_MarbleGrass,
		TerrainResources::MarbleGrass_MarbleGrassTopLeft,
		TerrainResources::MarbleGrass_MarbleGrassTopRight,
		TerrainResources::MarbleGrass_MarbleGrassBottom,
		TerrainResources::MarbleGrass_MarbleGrassBottomLeft,
		TerrainResources::MarbleGrass_MarbleGrassBottomRight,
		TerrainResources::MarbleGrass_MarbleGrassLeft,
		TerrainResources::MarbleGrass_MarbleGrassRight,
		Color4B(11, 30, 39, 255)))
{
}

MarbleGrassTerrain::~MarbleGrassTerrain()
{
}
