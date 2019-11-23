#include "CaveTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CaveTerrain::MapKeyTerrainType = "cave";

CaveTerrain* CaveTerrain::create(ValueMap& properties)
{
	CaveTerrain* instance = new CaveTerrain(properties);

	instance->autorelease();

	return instance;
}

CaveTerrain::CaveTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		CaveTerrain::MapKeyTerrainType,
		TextureResources::CaveTexture,
		TerrainResources::Cave_Top,
		TerrainResources::Cave_TopLeft,
		TerrainResources::Cave_TopRight,
		TerrainResources::Cave_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::Cave_Bottom,
		TerrainResources::Cave_BottomLeft,
		TerrainResources::Cave_BottomRight,
		TerrainResources::Cave_BottomConnector,
		TerrainResources::Cave_Left,
		TerrainResources::Cave_LeftConnector,
		TerrainResources::Cave_Right,
		TerrainResources::Cave_RightConnector,
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

CaveTerrain::~CaveTerrain()
{
}
