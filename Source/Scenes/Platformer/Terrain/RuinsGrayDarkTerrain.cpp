#include "RuinsGrayDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/RuinsGrayDarkTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsGrayDarkTerrain::MapKey = "ruins-gray-dark";

RuinsGrayDarkTerrain* RuinsGrayDarkTerrain::create(ValueMap& properties)
{
	RuinsGrayDarkTerrain* instance = new RuinsGrayDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

RuinsGrayDarkTerrain::RuinsGrayDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return RuinsGrayDarkTexture::create(transformedProps);
		},
		0.5f,
		RuinsGrayDarkTerrain::MapKey,
		TextureResources::RuinsGrayDarkTexture,
		TerrainResources::RuinsGrayThick_Top,
		TerrainResources::RuinsGrayThick_TopLeft,
		TerrainResources::RuinsGrayThick_TopRight,
		TerrainResources::RuinsGrayThick_TopConnector,
		TerrainResources::RuinsGrayThick_TopConnectorConcave,
		TerrainResources::RuinsGrayThick_TopConnectorConcaveDeep,
		TerrainResources::RuinsGrayThick_TopConnectorConvex,
		TerrainResources::RuinsGrayThick_TopConnectorConvexDeep,
		TerrainResources::RuinsGrayThick_Bottom,
		TerrainResources::RuinsGrayThick_BottomLeft,
		TerrainResources::RuinsGrayThick_BottomRight,
		TerrainResources::RuinsGrayThick_BottomConnector,
		TerrainResources::RuinsGrayThick_Left,
		TerrainResources::RuinsGrayThick_LeftConnector,
		TerrainResources::RuinsGrayThick_Right,
		TerrainResources::RuinsGrayThick_RightConnector,
		// Top
		Vec2(0.0f, -44.0f),
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2(0.0f, -2.0f),
		// TopRight
		Vec2(0.0f, -2.0f),
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
		Vec2(0.0f, -6.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -8.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

RuinsGrayDarkTerrain::~RuinsGrayDarkTerrain()
{
}
