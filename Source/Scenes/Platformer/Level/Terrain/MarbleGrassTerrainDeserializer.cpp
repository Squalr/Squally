#include "MarbleGrassTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string MarbleGrassTerrainDeserializer::MapKeyTerrainTypeMarbleGrass = "marble-grass";

MarbleGrassTerrainDeserializer* MarbleGrassTerrainDeserializer::create()
{
	MarbleGrassTerrainDeserializer* instance = new MarbleGrassTerrainDeserializer();

	instance->autorelease();

	return instance;
}

MarbleGrassTerrainDeserializer::MarbleGrassTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		MarbleGrassTerrainDeserializer::MapKeyTerrainTypeMarbleGrass,
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

MarbleGrassTerrainDeserializer::~MarbleGrassTerrainDeserializer()
{
}
