#include "DryGrassTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryGrassTerrainDeserializer::MapKeyTerrainTypeDryGrass = "dry-grass";
DryGrassTerrainDeserializer* DryGrassTerrainDeserializer::instance = nullptr;

void DryGrassTerrainDeserializer::registerGlobalNode()
{
	if (DryGrassTerrainDeserializer::instance == nullptr)
	{
		DryGrassTerrainDeserializer::instance = new DryGrassTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(DryGrassTerrainDeserializer::instance);
	}
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
