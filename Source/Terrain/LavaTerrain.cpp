#include "LavaTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string LavaTerrain::MapKeyTerrainTypeLava = "lava";

LavaTerrain* LavaTerrain::create(ValueMap& properties)
{
	LavaTerrain* instance = new LavaTerrain(properties);

	instance->autorelease();

	return instance;
}

LavaTerrain::LavaTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		LavaTerrain::MapKeyTerrainTypeLava,
		TerrainResources::Lava_LavaTexture,
		TerrainResources::Lava_Lava,
		TerrainResources::Lava_LavaTopLeft,
		TerrainResources::Lava_LavaTopRight,
		TerrainResources::Lava_LavaBottom,
		TerrainResources::Lava_LavaBottomLeft,
		TerrainResources::Lava_LavaBottomRight,
		TerrainResources::Lava_LavaLeft,
		TerrainResources::Lava_LavaRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

LavaTerrain::~LavaTerrain()
{
}
