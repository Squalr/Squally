#include "RuinsThickTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/RuinsTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsThickTerrain::MapKey = "ruins-thick";

RuinsThickTerrain* RuinsThickTerrain::create(ValueMap& properties)
{
	RuinsThickTerrain* instance = new RuinsThickTerrain(properties);

	instance->autorelease();

	return instance;
}

RuinsThickTerrain::RuinsThickTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return RuinsTexture::create(transformedProps);
		},
		0.5f,
		RuinsThickTerrain::MapKey,
		TextureResources::RuinsTexture,
		TerrainResources::RuinsThick_Top,
		TerrainResources::RuinsThick_TopLeft,
		TerrainResources::RuinsThick_TopRight,
		TerrainResources::RuinsThick_TopConnector,
		TerrainResources::RuinsThick_TopConnectorConcave,
		TerrainResources::RuinsThick_TopConnectorConcaveDeep,
		TerrainResources::RuinsThick_TopConnectorConvex,
		TerrainResources::RuinsThick_TopConnectorConvexDeep,
		TerrainResources::RuinsThick_Bottom,
		TerrainResources::RuinsThick_BottomLeft,
		TerrainResources::RuinsThick_BottomRight,
		TerrainResources::RuinsThick_BottomConnector,
		TerrainResources::RuinsThick_Left,
		TerrainResources::RuinsThick_LeftConnector,
		TerrainResources::RuinsThick_Right,
		TerrainResources::RuinsThick_RightConnector,
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

RuinsThickTerrain::~RuinsThickTerrain()
{
}
