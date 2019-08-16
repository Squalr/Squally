#include "JungleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string JungleTerrain::MapKeyTerrainTypeJungle = "jungle";

JungleTerrain* JungleTerrain::create(ValueMap& properties)
{
	JungleTerrain* instance = new JungleTerrain(properties);

	instance->autorelease();

	return instance;
}

JungleTerrain::JungleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		JungleTerrain::MapKeyTerrainTypeJungle,
		TerrainResources::Jungle_JungleTexture,
		TerrainResources::Jungle_Jungle,
		TerrainResources::Jungle_JungleTopLeft,
		TerrainResources::Jungle_JungleTopRight,
		TerrainResources::Jungle_JungleBottom,
		TerrainResources::Jungle_JungleBottomLeft,
		TerrainResources::Jungle_JungleBottomRight,
		TerrainResources::Jungle_JungleLeft,
		TerrainResources::Jungle_JungleRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

JungleTerrain::~JungleTerrain()
{
}
