#include "RailsTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RailsTerrain::MapKey = "rails";

RailsTerrain* RailsTerrain::create(ValueMap& properties)
{
	RailsTerrain* instance = new RailsTerrain(properties);

	instance->autorelease();

	return instance;
}

RailsTerrain::RailsTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			return nullptr;
		},
		0.5f,
		RailsTerrain::MapKey,
		// No texture
		"",
		TerrainResources::Rails_Top,
		TerrainResources::Rails_TopLeft,
		TerrainResources::Rails_TopRight,
		TerrainResources::Rails_TopConnector,
		TerrainResources::Rails_TopConnectorConcave,
		TerrainResources::Rails_TopConnectorConcaveDeep,
		TerrainResources::Rails_TopConnectorConvex,
		TerrainResources::Rails_TopConnectorConvexDeep,
		// No bottoms
		"",
		"",
		"",
		"",
		// No left/right
		"",
		"",
		"",
		"",
		// Top
		Vec2::ZERO,
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2(-58.0f, -8.0f),
		// TopRight
		Vec2(40.0f, 6.0f),
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

RailsTerrain::~RailsTerrain()
{
}
