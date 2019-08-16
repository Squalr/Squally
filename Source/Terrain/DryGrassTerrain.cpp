#include "DryGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string DryGrassTerrain::MapKeyTerrainTypeDryGrass = "dry-grass";

DryGrassTerrain* DryGrassTerrain::create(ValueMap& properties)
{
	DryGrassTerrain* instance = new DryGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

DryGrassTerrain::DryGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		DryGrassTerrain::MapKeyTerrainTypeDryGrass,
		TerrainResources::DryGrass_DryGrassTexture,
		TerrainResources::DryGrass_DryGrass,
		TerrainResources::DryGrass_DryGrassTopLeft,
		TerrainResources::DryGrass_DryGrassTopRight,
		TerrainResources::DryGrass_DryGrassBottom,
		TerrainResources::DryGrass_DryGrassBottomLeft,
		TerrainResources::DryGrass_DryGrassBottomRight,
		TerrainResources::DryGrass_DryGrassLeft,
		TerrainResources::DryGrass_DryGrassRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

DryGrassTerrain::~DryGrassTerrain()
{
}
