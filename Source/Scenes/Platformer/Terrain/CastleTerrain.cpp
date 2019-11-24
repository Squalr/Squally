#include "CastleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CastleTerrain::MapKeyTerrainType = "castle";

CastleTerrain* CastleTerrain::create(ValueMap& properties)
{
	CastleTerrain* instance = new CastleTerrain(properties);

	instance->autorelease();

	return instance;
}

CastleTerrain::CastleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		CastleTerrain::MapKeyTerrainType,
		TextureResources::CastleTexture,
		TerrainResources::Castle_Top,
		TerrainResources::Castle_TopLeft,
		TerrainResources::Castle_TopRight,
		TerrainResources::Castle_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Castle_Bottom,
		TerrainResources::Castle_BottomLeft,
		TerrainResources::Castle_BottomRight,
		TerrainResources::Castle_BottomConnector,
		TerrainResources::Castle_Left,
		TerrainResources::Castle_LeftConnector,
		TerrainResources::Castle_Right,
		TerrainResources::Castle_RightConnector,
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
		Color4B(11, 30, 39, 255)))
{
}

CastleTerrain::~CastleTerrain()
{
}
