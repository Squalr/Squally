#include "DryGrassTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryGrassTerrainDeserializer::MapKeyTerrainTypeDryGrass = "dry-grass";

DryGrassTerrainDeserializer* DryGrassTerrainDeserializer::create()
{
	DryGrassTerrainDeserializer* instance = new DryGrassTerrainDeserializer();

	instance->autorelease();

	return instance;
}

DryGrassTerrainDeserializer::DryGrassTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		DryGrassTerrainDeserializer::MapKeyTerrainTypeDryGrass,
		TerrainResources::DryGrass_DryGrassTexture,
		TerrainResources::DryGrass_DryGrass,
		TerrainResources::DryGrass_DryGrassTopLeft,
		TerrainResources::DryGrass_DryGrassTopRight,
		TerrainResources::DryGrass_DryGrassBottom,
		TerrainResources::DryGrass_DryGrassBottomLeft,
		TerrainResources::DryGrass_DryGrassBottomRight,
		TerrainResources::DryGrass_DryGrassLeft,
		TerrainResources::DryGrass_DryGrassRight,
		Color4B(11, 30, 39, 255)))
{
}

DryGrassTerrainDeserializer::~DryGrassTerrainDeserializer()
{
}
