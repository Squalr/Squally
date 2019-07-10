#include "FrostTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string FrostTerrain::MapKeyTerrainTypeFrost = "frost";

FrostTerrain* FrostTerrain::create(ValueMap& initProperties)
{
	FrostTerrain* instance = new FrostTerrain(initProperties);

	instance->autorelease();

	return instance;
}

FrostTerrain::FrostTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		FrostTerrain::MapKeyTerrainTypeFrost,
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

FrostTerrain::~FrostTerrain()
{
}
