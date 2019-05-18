#include "ShadeGrassTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string ShadeGrassTerrainDeserializer::MapKeyTerrainTypeShadeGrass = "shade-grass";
ShadeGrassTerrainDeserializer* ShadeGrassTerrainDeserializer::instance = nullptr;

void ShadeGrassTerrainDeserializer::registerGlobalNode()
{
	if (ShadeGrassTerrainDeserializer::instance == nullptr)
	{
		ShadeGrassTerrainDeserializer::instance = new ShadeGrassTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(ShadeGrassTerrainDeserializer::instance);
	}
}

ShadeGrassTerrainDeserializer::ShadeGrassTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		ShadeGrassTerrainDeserializer::MapKeyTerrainTypeShadeGrass,
		TerrainResources::ShadeGrass_ShadeGrassTexture,
		TerrainResources::ShadeGrass_ShadeGrass,
		TerrainResources::ShadeGrass_ShadeGrassTopLeft,
		TerrainResources::ShadeGrass_ShadeGrassTopRight,
		TerrainResources::ShadeGrass_ShadeGrassBottom,
		TerrainResources::ShadeGrass_ShadeGrassBottomLeft,
		TerrainResources::ShadeGrass_ShadeGrassBottomRight,
		TerrainResources::ShadeGrass_ShadeGrassLeft,
		TerrainResources::ShadeGrass_ShadeGrassRight,
		Color4B(11, 30, 39, 255)))
{
}

ShadeGrassTerrainDeserializer::~ShadeGrassTerrainDeserializer()
{
}
