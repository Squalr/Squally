#include "LavaTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LavaTerrain::MapKeyTerrainType = "lava";

LavaTerrain* LavaTerrain::create(ValueMap& properties)
{
	LavaTerrain* instance = new LavaTerrain(properties);

	instance->autorelease();

	return instance;
}

LavaTerrain::LavaTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		LavaTerrain::MapKeyTerrainType,
		TextureResources::LavaTexture,
		TerrainResources::Lava_Top,
		TerrainResources::Lava_TopLeft,
		TerrainResources::Lava_TopRight,
		TerrainResources::Lava_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Lava_Bottom,
		TerrainResources::Lava_BottomLeft,
		TerrainResources::Lava_BottomRight,
		TerrainResources::Lava_BottomConnector,
		TerrainResources::Lava_Left,
		TerrainResources::Lava_LeftConnector,
		TerrainResources::Lava_Right,
		TerrainResources::Lava_RightConnector,
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

LavaTerrain::~LavaTerrain()
{
}
