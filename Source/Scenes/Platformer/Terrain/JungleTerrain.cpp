#include "JungleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string JungleTerrain::MapKeyTerrainType = "jungle";

JungleTerrain* JungleTerrain::create(ValueMap& properties)
{
	JungleTerrain* instance = new JungleTerrain(properties);

	instance->autorelease();

	return instance;
}

JungleTerrain::JungleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		JungleTerrain::MapKeyTerrainType,
		TextureResources::JungleTexture,
		TerrainResources::Jungle_Top,
		TerrainResources::Jungle_TopLeft,
		TerrainResources::Jungle_TopRight,
		TerrainResources::Jungle_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Jungle_Bottom,
		TerrainResources::Jungle_BottomLeft,
		TerrainResources::Jungle_BottomRight,
		TerrainResources::Jungle_BottomConnector,
		TerrainResources::Jungle_Left,
		TerrainResources::Jungle_LeftConnector,
		TerrainResources::Jungle_Right,
		TerrainResources::Jungle_RightConnector,
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

JungleTerrain::~JungleTerrain()
{
}
