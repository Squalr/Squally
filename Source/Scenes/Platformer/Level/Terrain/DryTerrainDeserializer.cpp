#include "DryTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryTerrainDeserializer::MapKeyTerrainTypeDry = "dry";

DryTerrainDeserializer* DryTerrainDeserializer::create()
{
	DryTerrainDeserializer* instance = new DryTerrainDeserializer();

	instance->autorelease();

	return instance;
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
