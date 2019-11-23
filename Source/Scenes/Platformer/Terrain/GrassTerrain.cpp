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
		TerrainResources::Grass_Top,
		TerrainResources::Grass_TopLeft,
		TerrainResources::Grass_TopRight,
		TerrainResources::Grass_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Grass_Bottom,
		TerrainResources::Grass_BottomLeft,
		TerrainResources::Grass_BottomRight,
		TerrainResources::Grass_BottomConnector,
		TerrainResources::Grass_Left,
		TerrainResources::Grass_LeftConnector,
		TerrainResources::Grass_Right,
		TerrainResources::Grass_RightConnector,
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

GrassTerrain::~GrassTerrain()
{
}
