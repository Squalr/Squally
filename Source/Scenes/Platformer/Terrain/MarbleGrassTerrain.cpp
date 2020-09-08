#include "MarbleGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/MarbleGrassTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleGrassTerrain::MapKey = "marble-grass";
const Color4B MarbleGrassTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B MarbleGrassTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

MarbleGrassTerrain* MarbleGrassTerrain::create(ValueMap& properties)
{
	MarbleGrassTerrain* instance = new MarbleGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleGrassTerrain::MarbleGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return MarbleGrassTexture::create(transformedProps);
		},
		0.5f,
		MarbleGrassTerrain::MapKey,
		TextureResources::MarbleGrassTexture,
		TerrainResources::MarbleGrass_Top,
		TerrainResources::MarbleGrass_TopLeft,
		TerrainResources::MarbleGrass_TopRight,
		TerrainResources::MarbleGrass_TopConnector,
		TerrainResources::MarbleGrass_TopConnectorConcave,
		TerrainResources::MarbleGrass_TopConnectorConcaveDeep,
		TerrainResources::MarbleGrass_TopConnectorConvex,
		TerrainResources::MarbleGrass_TopConnectorConvexDeep,
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
		// TopConnector
		Vec2::ZERO,
		// TopConnectorConcave
		Vec2(0.0f, 4.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 6.0f),
		// TopConnectorConvex
		Vec2(0.0f, -2.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -14.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		InfillData(MarbleGrassTerrain::FillColor, false, true, true)))
{
}

MarbleGrassTerrain::~MarbleGrassTerrain()
{
}
