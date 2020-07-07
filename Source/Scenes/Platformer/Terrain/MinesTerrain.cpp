#include "MinesTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/MinesTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MinesTerrain::MapKey = "mines";

MinesTerrain* MinesTerrain::create(ValueMap& properties)
{
	MinesTerrain* instance = new MinesTerrain(properties);

	instance->autorelease();

	return instance;
}

MinesTerrain::MinesTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return MinesTexture::create(transformedProps);
		},
		0.5f,
		MinesTerrain::MapKey,
		TextureResources::MinesTexture,
		TerrainResources::Mines_Top,
		TerrainResources::Mines_TopLeft,
		TerrainResources::Mines_TopRight,
		TerrainResources::Mines_TopConnector,
		TerrainResources::Mines_TopConnectorConcave,
		TerrainResources::Mines_TopConnectorConcaveDeep,
		TerrainResources::Mines_TopConnectorConvex,
		TerrainResources::Mines_TopConnectorConvexDeep,
		TerrainResources::Mines_Bottom,
		TerrainResources::Mines_BottomLeft,
		TerrainResources::Mines_BottomRight,
		TerrainResources::Mines_BottomConnector,
		TerrainResources::Mines_Left,
		TerrainResources::Mines_LeftConnector,
		TerrainResources::Mines_Right,
		TerrainResources::Mines_RightConnector,
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
		Color4B(14, 5, 2, 255)))
{
}

MinesTerrain::~MinesTerrain()
{
}
