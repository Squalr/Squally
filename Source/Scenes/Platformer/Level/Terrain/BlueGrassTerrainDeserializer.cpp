#include "BlueGrassTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string BlueGrassTerrainDeserializer::MapKeyTerrainTypeBlueGrass = "blue-grass";
BlueGrassTerrainDeserializer* BlueGrassTerrainDeserializer::instance = nullptr;

void BlueGrassTerrainDeserializer::registerGlobalNode()
{
	if (BlueGrassTerrainDeserializer::instance == nullptr)
	{
		BlueGrassTerrainDeserializer::instance = new BlueGrassTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(BlueGrassTerrainDeserializer::instance);
	}
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
