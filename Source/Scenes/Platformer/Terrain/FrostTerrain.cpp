#include "FrostTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string FrostTerrain::MapKeyTerrainType = "frost";

FrostTerrain* FrostTerrain::create(ValueMap& properties)
{
	FrostTerrain* instance = new FrostTerrain(properties);

	instance->autorelease();

	return instance;
}

FrostTerrain::FrostTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		FrostTerrain::MapKeyTerrainType,
		TextureResources::FrostTexture,
		TerrainResources::Frost_Top,
		TerrainResources::Frost_TopLeft,
		TerrainResources::Frost_TopRight,
		TerrainResources::Frost_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Frost_Bottom,
		TerrainResources::Frost_BottomLeft,
		TerrainResources::Frost_BottomRight,
		TerrainResources::Frost_BottomConnector,
		TerrainResources::Frost_Left,
		TerrainResources::Frost_LeftConnector,
		TerrainResources::Frost_Right,
		TerrainResources::Frost_RightConnector,
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

FrostTerrain::~FrostTerrain()
{
}
