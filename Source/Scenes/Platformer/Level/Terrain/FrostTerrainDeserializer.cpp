#include "FrostTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string FrostTerrainDeserializer::MapKeyTerrainTypeFrost = "frost";
FrostTerrainDeserializer* FrostTerrainDeserializer::instance = nullptr;

void FrostTerrainDeserializer::registerGlobalNode()
{
	if (FrostTerrainDeserializer::instance == nullptr)
	{
		FrostTerrainDeserializer::instance = new FrostTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(FrostTerrainDeserializer::instance);
	}
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
