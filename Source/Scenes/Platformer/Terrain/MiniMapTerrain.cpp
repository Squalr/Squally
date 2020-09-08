#include "MiniMapTerrain.h"

#include "cocos/base/CCValue.h"

using namespace cocos2d;

const std::string MiniMapTerrain::MapKey = "mini-map";

MiniMapTerrain* MiniMapTerrain::create(ValueMap& properties, Color4B drawColor)
{
	MiniMapTerrain* instance = new MiniMapTerrain(properties, drawColor);

	instance->autorelease();

	return instance;
}

MiniMapTerrain::MiniMapTerrain(ValueMap& properties, Color4B drawColor) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			return nullptr;
		},
		0.5f,
		MiniMapTerrain::MapKey,
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
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
		Vec2(0.0f, 0.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 0.0f),
		// TopConnectorConvex
		Vec2(0.0f, 0.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, 0.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		InfillData(drawColor, true, false, false),
		false,
		false))
{
}

MiniMapTerrain::~MiniMapTerrain()
{
}
