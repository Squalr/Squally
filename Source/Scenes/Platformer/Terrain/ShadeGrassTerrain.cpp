#include "ShadeGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShadeGrassTerrain::MapKeyTerrainType = "shade-grass";

ShadeGrassTerrain* ShadeGrassTerrain::create(ValueMap& properties)
{
	ShadeGrassTerrain* instance = new ShadeGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

ShadeGrassTerrain::ShadeGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		ShadeGrassTerrain::MapKeyTerrainType,
		TextureResources::ShadeGrassTexture,
		TerrainResources::ShadeGrass_ShadeGrass,
		TerrainResources::ShadeGrass_ShadeGrassTopLeft,
		TerrainResources::ShadeGrass_ShadeGrassTopRight,
		TerrainResources::ShadeGrass_ShadeGrassBottom,
		TerrainResources::ShadeGrass_ShadeGrassBottomLeft,
		TerrainResources::ShadeGrass_ShadeGrassBottomRight,
		TerrainResources::ShadeGrass_ShadeGrassLeft,
		TerrainResources::ShadeGrass_ShadeGrassRight,
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

ShadeGrassTerrain::~ShadeGrassTerrain()
{
}
