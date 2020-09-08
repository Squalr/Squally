#include "StoneDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/StoneTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string StoneDarkTerrain::MapKey = "stone-dark";
const Color4B StoneDarkTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B StoneDarkTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

StoneDarkTerrain* StoneDarkTerrain::create(ValueMap& properties)
{
	StoneDarkTerrain* instance = new StoneDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

StoneDarkTerrain::StoneDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return StoneTexture::create(transformedProps);
		},
		0.5f,
		StoneDarkTerrain::MapKey,
		TextureResources::StoneTexture,
		TerrainResources::Stone_Top,
		TerrainResources::Stone_TopLeft,
		TerrainResources::Stone_TopRight,
		TerrainResources::Stone_TopConnector,
		TerrainResources::Stone_TopConnectorConcave,
		TerrainResources::Stone_TopConnectorConcaveDeep,
		TerrainResources::Stone_TopConnectorConvex,
		TerrainResources::Stone_TopConnectorConvexDeep,
		TerrainResources::Stone_Bottom,
		TerrainResources::Stone_BottomLeft,
		TerrainResources::Stone_BottomRight,
		TerrainResources::Stone_BottomConnector,
		TerrainResources::Stone_Left,
		TerrainResources::Stone_LeftConnector,
		TerrainResources::Stone_Right,
		TerrainResources::Stone_RightConnector,
		// Top
		Vec2(0.0f, -24.0f),
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
		InfillData(StoneDarkTerrain::FillColor, false, true, true)))
{
}

StoneDarkTerrain::~StoneDarkTerrain()
{
}
