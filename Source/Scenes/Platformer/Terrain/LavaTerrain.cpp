#include "LavaTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LavaTerrain::MapKeyTerrainType = "lava";

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
		LavaTerrain::MapKeyTerrainType,
		TextureResources::LavaTexture,
		TerrainResources::Lava_Lava,
		TerrainResources::Lava_LavaTopLeft,
		TerrainResources::Lava_LavaTopRight,
		TerrainResources::Lava_LavaBottom,
		TerrainResources::Lava_LavaBottomLeft,
		TerrainResources::Lava_LavaBottomRight,
		TerrainResources::Lava_LavaLeft,
		TerrainResources::Lava_LavaRight,
		// Top
		Vec2::ZERO,
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2::ZERO,
		// TopRight
		Vec2::ZERO,
		// BottomLeft
		Vec2::ZERO,
		// BottomRight
		Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

LavaTerrain::~LavaTerrain()
{
}
