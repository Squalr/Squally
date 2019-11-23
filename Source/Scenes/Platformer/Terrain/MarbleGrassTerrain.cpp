#include "MarbleGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleGrassTerrain::MapKeyTerrainType = "marble-grass";

MarbleGrassTerrain* MarbleGrassTerrain::create(ValueMap& properties)
{
	MarbleGrassTerrain* instance = new MarbleGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleGrassTerrain::MarbleGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		MarbleGrassTerrain::MapKeyTerrainType,
		TextureResources::MarbleGrassTexture,
		TerrainResources::MarbleGrass_Top,
		TerrainResources::MarbleGrass_TopLeft,
		TerrainResources::MarbleGrass_TopRight,
		TerrainResources::MarbleGrass_TopConnector,
		TerrainResources::BlueGrass_TopConnectorConcave,
		TerrainResources::BlueGrass_TopConnectorConcaveDeep,
		TerrainResources::BlueGrass_TopConnectorConvex,
		TerrainResources::BlueGrass_TopConnectorConvexDeep,
		TerrainResources::MarbleGrass_Bottom,
		TerrainResources::MarbleGrass_BottomLeft,
		TerrainResources::MarbleGrass_BottomRight,
		TerrainResources::MarbleGrass_BottomConnector,
		TerrainResources::MarbleGrass_Left,
		TerrainResources::MarbleGrass_LeftConnector,
		TerrainResources::MarbleGrass_Right,
		TerrainResources::MarbleGrass_RightConnector,
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

MarbleGrassTerrain::~MarbleGrassTerrain()
{
}
