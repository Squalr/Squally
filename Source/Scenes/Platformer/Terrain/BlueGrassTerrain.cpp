#include "BlueGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string BlueGrassTerrain::MapKeyTerrainType = "blue-grass";

BlueGrassTerrain* BlueGrassTerrain::create(ValueMap& properties)
{
	BlueGrassTerrain* instance = new BlueGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

BlueGrassTerrain::BlueGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		BlueGrassTerrain::MapKeyTerrainType,
		TextureResources::BlueGrassTexture,
		TerrainResources::BlueGrass_Top,
		TerrainResources::BlueGrass_TopLeft,
		TerrainResources::BlueGrass_TopRight,
		TerrainResources::BlueGrass_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::BlueGrass_Bottom,
		TerrainResources::BlueGrass_BottomLeft,
		TerrainResources::BlueGrass_BottomRight,
		TerrainResources::BlueGrass_BottomConnector,
		TerrainResources::BlueGrass_Left,
		TerrainResources::BlueGrass_LeftConnector,
		TerrainResources::BlueGrass_Right,
		TerrainResources::BlueGrass_RightConnector,
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
		// TopConnector
		Vec2::ZERO,
		// TopConnectorConcave
		Vec2(0.0f, 4.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 6.0f),
		// TopConnectorConvex
		Vec2(0.0f, -8.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -14.0f),
		Color4B(11, 30, 39, 255)))
{
}

BlueGrassTerrain::~BlueGrassTerrain()
{
}
