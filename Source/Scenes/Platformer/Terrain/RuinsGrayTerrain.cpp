#include "RuinsGrayTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/RuinsGrayTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsGrayTerrain::MapKey = "ruins-gray";

RuinsGrayTerrain* RuinsGrayTerrain::create(ValueMap& properties)
{
	RuinsGrayTerrain* instance = new RuinsGrayTerrain(properties);

	instance->autorelease();

	return instance;
}

RuinsGrayTerrain::RuinsGrayTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return RuinsGrayTexture::create(transformedProps);
		},
		0.5f,
		RuinsGrayTerrain::MapKey,
		TextureResources::RuinsGrayTexture,
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

RuinsGrayTerrain::~RuinsGrayTerrain()
{
}
