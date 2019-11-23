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
		TerrainResources::ShadeGrass_Top,
		TerrainResources::ShadeGrass_TopLeft,
		TerrainResources::ShadeGrass_TopRight,
		TerrainResources::ShadeGrass_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::ShadeGrass_Bottom,
		TerrainResources::ShadeGrass_BottomLeft,
		TerrainResources::ShadeGrass_BottomRight,
		TerrainResources::ShadeGrass_BottomConnector,
		TerrainResources::ShadeGrass_Left,
		TerrainResources::ShadeGrass_LeftConnector,
		TerrainResources::ShadeGrass_Right,
		TerrainResources::ShadeGrass_RightConnector,
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
