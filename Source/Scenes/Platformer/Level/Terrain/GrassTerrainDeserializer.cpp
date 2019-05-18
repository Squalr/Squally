#include "GrassTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string GrassTerrainDeserializer::MapKeyTerrainTypeGrass = "grass";
GrassTerrainDeserializer* GrassTerrainDeserializer::instance = nullptr;

void GrassTerrainDeserializer::registerGlobalNode()
{
	if (GrassTerrainDeserializer::instance == nullptr)
	{
		GrassTerrainDeserializer::instance = new GrassTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(GrassTerrainDeserializer::instance);
	}
}

GrassTerrainDeserializer::GrassTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		GrassTerrainDeserializer::MapKeyTerrainTypeGrass,
		TerrainResources::Grass_GrassTexture,
		TerrainResources::Grass_Grass,
		TerrainResources::Grass_GrassTopLeft,
		TerrainResources::Grass_GrassTopRight,
		TerrainResources::Grass_GrassBottom,
		TerrainResources::Grass_GrassBottomLeft,
		TerrainResources::Grass_GrassBottomRight,
		TerrainResources::Grass_GrassLeft,
		TerrainResources::Grass_GrassRight,
		Color4B(11, 30, 39, 255)))
{
}

GrassTerrainDeserializer::~GrassTerrainDeserializer()
{
}
