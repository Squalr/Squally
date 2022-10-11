#include "WoodBlackFillTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/BlackTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string WoodBlackFillTerrain::MapKey = "wood-black-fill";
const Color4B WoodBlackFillTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B WoodBlackFillTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

WoodBlackFillTerrain* WoodBlackFillTerrain::create(ValueMap& properties)
{
	WoodBlackFillTerrain* instance = new WoodBlackFillTerrain(properties);

	instance->autorelease();

	return instance;
}

WoodBlackFillTerrain::WoodBlackFillTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return BlackTexture::create(transformedProps);
		},
		0.5f,
		WoodBlackFillTerrain::MapKey,
		TextureResources::WoodTexture,
		TerrainResources::Wood_Top,
		TerrainResources::Wood_TopLeft,
		TerrainResources::Wood_TopRight,
		TerrainResources::Wood_TopConnector,
		TerrainResources::Wood_TopConnectorConcave,
		TerrainResources::Wood_TopConnectorConcaveDeep,
		TerrainResources::Wood_TopConnectorConvex,
		TerrainResources::Wood_TopConnectorConvexDeep,
		TerrainResources::Wood_Bottom,
		TerrainResources::Wood_BottomLeft,
		TerrainResources::Wood_BottomRight,
		TerrainResources::Wood_BottomConnector,
		TerrainResources::Wood_Left,
		TerrainResources::Wood_LeftConnector,
		TerrainResources::Wood_Right,
		TerrainResources::Wood_RightConnector,
		// Top
		Vec2(0.0f, -42.0f),
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
		InfillData(WoodBlackFillTerrain::FillColor, false, true)))
{
}

WoodBlackFillTerrain::~WoodBlackFillTerrain()
{
}
