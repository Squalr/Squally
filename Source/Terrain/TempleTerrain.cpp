#include "TempleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string TempleTerrain::MapKeyTerrainTypeTemple = "temple";

TempleTerrain* TempleTerrain::create(ValueMap& properties)
{
	TempleTerrain* instance = new TempleTerrain(properties);

	instance->autorelease();

	return instance;
}

TempleTerrain::TempleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		TempleTerrain::MapKeyTerrainTypeTemple,
		TerrainResources::Temple_TempleTexture,
		TerrainResources::Temple_Temple,
		TerrainResources::Temple_TempleTopLeft,
		TerrainResources::Temple_TempleTopRight,
		TerrainResources::Temple_TempleBottom,
		TerrainResources::Temple_TempleBottomLeft,
		TerrainResources::Temple_TempleBottomRight,
		TerrainResources::Temple_TempleLeft,
		TerrainResources::Temple_TempleRight,
		cocos2d::Vec2(0.0f, -16.0f),
		cocos2d::Vec2(-56.0f, 0.0f),
		cocos2d::Vec2(56.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

TempleTerrain::~TempleTerrain()
{
}
