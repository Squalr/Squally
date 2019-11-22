#include "GrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string GrassTerrain::MapKeyTerrainType = "grass";

GrassTerrain* GrassTerrain::create(ValueMap& properties)
{
	GrassTerrain* instance = new GrassTerrain(properties);

	instance->autorelease();

	return instance;
}

GrassTerrain::GrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		GrassTerrain::MapKeyTerrainType,
		TextureResources::GrassTexture,
		TerrainResources::Grass_Grass,
		TerrainResources::Grass_GrassTopLeft,
		TerrainResources::Grass_GrassTopRight,
		TerrainResources::Grass_GrassBottom,
		TerrainResources::Grass_GrassBottomLeft,
		TerrainResources::Grass_GrassBottomRight,
		TerrainResources::Grass_GrassLeft,
		TerrainResources::Grass_GrassRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

GrassTerrain::~GrassTerrain()
{
}
