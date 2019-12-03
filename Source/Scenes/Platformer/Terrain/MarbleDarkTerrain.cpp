#include "MarbleDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleDarkTerrain::MapKeyTerrainType = "marble-dark";

MarbleDarkTerrain* MarbleDarkTerrain::create(ValueMap& properties)
{
	MarbleDarkTerrain* instance = new MarbleDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleDarkTerrain::MarbleDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		MarbleDarkTerrain::MapKeyTerrainType,
		TextureResources::MarbleDarkTexture,
		TerrainResources::MarbleDark_Top,
		TerrainResources::MarbleDark_TopLeft,
		TerrainResources::MarbleDark_TopRight,
		TerrainResources::MarbleDark_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::MarbleDark_Bottom,
		TerrainResources::MarbleDark_BottomLeft,
		TerrainResources::MarbleDark_BottomRight,
		TerrainResources::MarbleDark_BottomConnector,
		TerrainResources::MarbleDark_Left,
		TerrainResources::MarbleDark_LeftConnector,
		TerrainResources::MarbleDark_Right,
		TerrainResources::MarbleDark_RightConnector,
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
		Vec2::ZERO,
		// TopConnectorConcaveDeep
		Vec2::ZERO,
		// TopConnectorConvex
		Vec2::ZERO,
		// TopConnectorConvexDeep
		Vec2::ZERO,
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

MarbleDarkTerrain::~MarbleDarkTerrain()
{
}
