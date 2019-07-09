#include "GrassTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string GrassTerrainDeserializer::MapKeyTerrainTypeGrass = "grass";

GrassTerrainDeserializer* GrassTerrainDeserializer::create()
{
	GrassTerrainDeserializer* instance = new GrassTerrainDeserializer();

	instance->autorelease();

	return instance;
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
