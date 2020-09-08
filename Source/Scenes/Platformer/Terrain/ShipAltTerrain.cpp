#include "ShipAltTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ShipAltTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipAltTerrain::MapKey = "ship-alt";
const Color4B ShipAltTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B ShipAltTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

ShipAltTerrain* ShipAltTerrain::create(ValueMap& properties)
{
	ShipAltTerrain* instance = new ShipAltTerrain(properties);

	instance->autorelease();

	return instance;
}

ShipAltTerrain::ShipAltTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return ShipAltTexture::create(transformedProps);
		},
		0.5f,
		ShipAltTerrain::MapKey,
		TextureResources::ShipAltTexture,
		TerrainResources::ShipAlt_Top,
		TerrainResources::ShipAlt_TopLeft,
		TerrainResources::ShipAlt_TopRight,
		TerrainResources::ShipAlt_TopConnector,
		TerrainResources::ShipAlt_TopConnectorConcave,
		TerrainResources::ShipAlt_TopConnectorConcaveDeep,
		TerrainResources::ShipAlt_TopConnectorConvex,
		TerrainResources::ShipAlt_TopConnectorConvexDeep,
		TerrainResources::ShipAlt_Bottom,
		TerrainResources::ShipAlt_BottomLeft,
		TerrainResources::ShipAlt_BottomRight,
		TerrainResources::ShipAlt_BottomConnector,
		TerrainResources::ShipAlt_Left,
		TerrainResources::ShipAlt_LeftConnector,
		TerrainResources::ShipAlt_Right,
		TerrainResources::ShipAlt_RightConnector,
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
		InfillData(ShipAltTerrain::FillColor, false, true, true)))
{
}

ShipAltTerrain::~ShipAltTerrain()
{
}
