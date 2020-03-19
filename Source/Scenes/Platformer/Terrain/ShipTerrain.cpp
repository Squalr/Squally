#include "ShipTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ShipTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShipTerrain::MapKey = "ship";

ShipTerrain* ShipTerrain::create(ValueMap& properties)
{
	ShipTerrain* instance = new ShipTerrain(properties);

	instance->autorelease();

	return instance;
}

ShipTerrain::ShipTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap& properties) { return ShipTexture::create(this->transformPropertiesForTexture(properties)); },
		0.5f,
		ShipTerrain::MapKey,
		TextureResources::ShipTexture,
		TerrainResources::Ship_Top,
		TerrainResources::Ship_TopLeft,
		TerrainResources::Ship_TopRight,
		TerrainResources::Ship_TopConnector,
		TerrainResources::Ship_TopConnectorConcave,
		TerrainResources::Ship_TopConnectorConcaveDeep,
		TerrainResources::Ship_TopConnectorConvex,
		TerrainResources::Ship_TopConnectorConvexDeep,
		TerrainResources::Ship_Bottom,
		TerrainResources::Ship_BottomLeft,
		TerrainResources::Ship_BottomRight,
		TerrainResources::Ship_BottomConnector,
		TerrainResources::Ship_Left,
		TerrainResources::Ship_LeftConnector,
		TerrainResources::Ship_Right,
		TerrainResources::Ship_RightConnector,
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
		Color4B(11, 30, 39, 255)))
{
}

ShipTerrain::~ShipTerrain()
{
}
