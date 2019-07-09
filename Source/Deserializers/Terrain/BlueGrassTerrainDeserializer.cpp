#include "BlueGrassTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string BlueGrassTerrainDeserializer::MapKeyTerrainTypeBlueGrass = "blue-grass";

BlueGrassTerrainDeserializer* BlueGrassTerrainDeserializer::create()
{
	BlueGrassTerrainDeserializer* instance = new BlueGrassTerrainDeserializer();

	instance->autorelease();

	return instance;
}

BlueGrassTerrainDeserializer::BlueGrassTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		BlueGrassTerrainDeserializer::MapKeyTerrainTypeBlueGrass,
		TerrainResources::BlueGrass_BlueGrassTexture,
		TerrainResources::BlueGrass_BlueGrass,
		TerrainResources::BlueGrass_BlueGrassTopLeft,
		TerrainResources::BlueGrass_BlueGrassTopRight,
		TerrainResources::BlueGrass_BlueGrassBottom,
		TerrainResources::BlueGrass_BlueGrassBottomLeft,
		TerrainResources::BlueGrass_BlueGrassBottomRight,
		TerrainResources::BlueGrass_BlueGrassLeft,
		TerrainResources::BlueGrass_BlueGrassRight,
		Color4B(11, 30, 39, 255)))
{
}

BlueGrassTerrainDeserializer::~BlueGrassTerrainDeserializer()
{
}
