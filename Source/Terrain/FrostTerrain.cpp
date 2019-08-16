#include "FrostTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string FrostTerrain::MapKeyTerrainTypeFrost = "frost";

FrostTerrain* FrostTerrain::create(ValueMap& properties)
{
	FrostTerrain* instance = new FrostTerrain(properties);

	instance->autorelease();

	return instance;
}

FrostTerrain::FrostTerrain(ValueMap& properties) : super(
	properties,
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
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

FrostTerrain::~FrostTerrain()
{
}
