#include "DryTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryTerrain::MapKeyTerrainTypeDry = "dry";

DryTerrain* DryTerrain::create(ValueMap& initProperties)
{
	DryTerrain* instance = new DryTerrain(initProperties);

	instance->autorelease();

	return instance;
}

DryTerrain::DryTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		DryTerrain::MapKeyTerrainTypeDry,
		TerrainResources::Dry_DryTexture,
		TerrainResources::Dry_Dry,
		TerrainResources::Dry_DryTopLeft,
		TerrainResources::Dry_DryTopRight,
		TerrainResources::Dry_DryBottom,
		TerrainResources::Dry_DryBottomLeft,
		TerrainResources::Dry_DryBottomRight,
		TerrainResources::Dry_DryLeft,
		TerrainResources::Dry_DryRight,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

DryTerrain::~DryTerrain()
{
}
