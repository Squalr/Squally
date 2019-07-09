#include "DarkGrassTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DarkGrassTerrainDeserializer::MapKeyTerrainTypeDarkGrass = "dark-grass";

DarkGrassTerrainDeserializer* DarkGrassTerrainDeserializer::create()
{
	DarkGrassTerrainDeserializer* instance = new DarkGrassTerrainDeserializer();

	instance->autorelease();

	return instance;
}

DarkGrassTerrainDeserializer::DarkGrassTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		DarkGrassTerrainDeserializer::MapKeyTerrainTypeDarkGrass,
		TerrainResources::DarkGrass_DarkGrassTexture,
		TerrainResources::DarkGrass_DarkGrass,
		TerrainResources::DarkGrass_DarkGrassTopLeft,
		TerrainResources::DarkGrass_DarkGrassTopRight,
		TerrainResources::DarkGrass_DarkGrassBottom,
		TerrainResources::DarkGrass_DarkGrassBottomLeft,
		TerrainResources::DarkGrass_DarkGrassBottomRight,
		TerrainResources::DarkGrass_DarkGrassLeft,
		TerrainResources::DarkGrass_DarkGrassRight,
		Color4B(11, 30, 39, 255)))
{
}

DarkGrassTerrainDeserializer::~DarkGrassTerrainDeserializer()
{
}
