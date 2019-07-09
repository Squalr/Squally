#include "FrostTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string FrostTerrainDeserializer::MapKeyTerrainTypeFrost = "frost";

FrostTerrainDeserializer* FrostTerrainDeserializer::create()
{
	FrostTerrainDeserializer* instance = new FrostTerrainDeserializer();

	instance->autorelease();

	return instance;
}

FrostTerrainDeserializer::FrostTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		FrostTerrainDeserializer::MapKeyTerrainTypeFrost,
		TerrainResources::Frost_FrostTexture,
		TerrainResources::Frost_Frost,
		TerrainResources::Frost_FrostTopLeft,
		TerrainResources::Frost_FrostTopRight,
		TerrainResources::Frost_FrostBottom,
		TerrainResources::Frost_FrostBottomLeft,
		TerrainResources::Frost_FrostBottomRight,
		TerrainResources::Frost_FrostLeft,
		TerrainResources::Frost_FrostRight,
		Color4B(11, 30, 39, 255)))
{
}

FrostTerrainDeserializer::~FrostTerrainDeserializer()
{
}
