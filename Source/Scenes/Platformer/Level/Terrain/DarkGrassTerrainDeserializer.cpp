#include "DarkGrassTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DarkGrassTerrainDeserializer::MapKeyTerrainTypeDarkGrass = "dark-grass";
DarkGrassTerrainDeserializer* DarkGrassTerrainDeserializer::instance = nullptr;

void DarkGrassTerrainDeserializer::registerGlobalNode()
{
	if (DarkGrassTerrainDeserializer::instance == nullptr)
	{
		DarkGrassTerrainDeserializer::instance = new DarkGrassTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(DarkGrassTerrainDeserializer::instance);
	}
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
