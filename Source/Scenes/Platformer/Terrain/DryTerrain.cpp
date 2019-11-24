#include "DryTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DryTerrain::MapKeyTerrainType = "dry";

DryTerrain* DryTerrain::create(ValueMap& properties)
{
	DryTerrain* instance = new DryTerrain(properties);

	instance->autorelease();

	return instance;
}

DryTerrain::DryTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		DryTerrain::MapKeyTerrainType,
		TextureResources::DryTexture,
		TerrainResources::Dry_Top,
		TerrainResources::Dry_TopLeft,
		TerrainResources::Dry_TopRight,
		TerrainResources::Dry_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Dry_Bottom,
		TerrainResources::Dry_BottomLeft,
		TerrainResources::Dry_BottomRight,
		TerrainResources::Dry_BottomConnector,
		TerrainResources::Dry_Left,
		TerrainResources::Dry_LeftConnector,
		TerrainResources::Dry_Right,
		TerrainResources::Dry_RightConnector,
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

DryTerrain::~DryTerrain()
{
}
