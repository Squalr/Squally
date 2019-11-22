#include "DarkGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DarkGrassTerrain::MapKeyTerrainType = "dark-grass";

DarkGrassTerrain* DarkGrassTerrain::create(ValueMap& properties)
{
	DarkGrassTerrain* instance = new DarkGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

DarkGrassTerrain::DarkGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		DarkGrassTerrain::MapKeyTerrainType,
		TextureResources::DarkGrassTexture,
		TerrainResources::DarkGrass_DarkGrass,
		TerrainResources::DarkGrass_DarkGrassTopLeft,
		TerrainResources::DarkGrass_DarkGrassTopRight,
		TerrainResources::DarkGrass_DarkGrassBottom,
		TerrainResources::DarkGrass_DarkGrassBottomLeft,
		TerrainResources::DarkGrass_DarkGrassBottomRight,
		TerrainResources::DarkGrass_DarkGrassLeft,
		TerrainResources::DarkGrass_DarkGrassRight,
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

DarkGrassTerrain::~DarkGrassTerrain()
{
}
