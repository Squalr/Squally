#include "GrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string GrassTerrain::MapKeyTerrainTypeGrass = "grass";

GrassTerrain* GrassTerrain::create(ValueMap& initProperties)
{
	GrassTerrain* instance = new GrassTerrain(initProperties);

	instance->autorelease();

	return instance;
}

GrassTerrain::GrassTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		GrassTerrain::MapKeyTerrainTypeGrass,
		TerrainResources::Grass_GrassTexture,
		TerrainResources::Grass_Grass,
		TerrainResources::Grass_GrassTopLeft,
		TerrainResources::Grass_GrassTopRight,
		TerrainResources::Grass_GrassBottom,
		TerrainResources::Grass_GrassBottomLeft,
		TerrainResources::Grass_GrassBottomRight,
		TerrainResources::Grass_GrassLeft,
		TerrainResources::Grass_GrassRight,
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
