#include "MarbleGrassTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string MarbleGrassTerrainDeserializer::MapKeyTerrainTypeMarbleGrass = "marble-grass";
MarbleGrassTerrainDeserializer* MarbleGrassTerrainDeserializer::instance = nullptr;

void MarbleGrassTerrainDeserializer::registerGlobalNode()
{
	if (MarbleGrassTerrainDeserializer::instance == nullptr)
	{
		MarbleGrassTerrainDeserializer::instance = new MarbleGrassTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(MarbleGrassTerrainDeserializer::instance);
	}
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
