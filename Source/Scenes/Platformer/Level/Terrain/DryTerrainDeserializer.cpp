#include "DryTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryTerrainDeserializer::MapKeyTerrainTypeDry = "dry";
DryTerrainDeserializer* DryTerrainDeserializer::instance = nullptr;

void DryTerrainDeserializer::registerGlobalNode()
{
	if (DryTerrainDeserializer::instance == nullptr)
	{
		DryTerrainDeserializer::instance = new DryTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(DryTerrainDeserializer::instance);
	}
}

DryTerrainDeserializer::DryTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		DryTerrainDeserializer::MapKeyTerrainTypeDry,
		TerrainResources::Dry_DryTexture,
		TerrainResources::Dry_Dry,
		TerrainResources::Dry_DryTopLeft,
		TerrainResources::Dry_DryTopRight,
		TerrainResources::Dry_DryBottom,
		TerrainResources::Dry_DryBottomLeft,
		TerrainResources::Dry_DryBottomRight,
		TerrainResources::Dry_DryLeft,
		TerrainResources::Dry_DryRight,
		Color4B(11, 30, 39, 255)))
{
}

DryTerrainDeserializer::~DryTerrainDeserializer()
{
}
