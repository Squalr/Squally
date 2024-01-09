#include "InvisibleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string InvisibleTerrain::MapKey = "invisible";
const Color4B InvisibleTerrain::FillColor = Color4B(0, 0, 0, 0);
const Color4B InvisibleTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

InvisibleTerrain* InvisibleTerrain::create(ValueMap& properties)
{
	InvisibleTerrain* instance = new InvisibleTerrain(properties);

	instance->autorelease();

	return instance;
}

InvisibleTerrain::InvisibleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			return nullptr;
		},
		0.5f,
		InvisibleTerrain::MapKey,
		// No texture
		"",
		// No tops
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
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
		Vec2(-58.0f, -7.0f),
		// TopRight
		Vec2(39.0f, 6.0f),
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
		InfillData(InvisibleTerrain::FillColor, false, true)))
{
}

InvisibleTerrain::~InvisibleTerrain()
{
}
