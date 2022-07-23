#include "VinesTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string VinesTerrain::MapKey = "vines";
const Color4B VinesTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B VinesTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

VinesTerrain* VinesTerrain::create(ValueMap& properties)
{
	VinesTerrain* instance = new VinesTerrain(properties);

	instance->autorelease();

	return instance;
}

VinesTerrain::VinesTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			return nullptr;
		},
		0.5f,
		VinesTerrain::MapKey,
		"",
		TerrainResources::Vines_Top,
		TerrainResources::Vines_TopLeft,
		TerrainResources::Vines_TopRight,
		TerrainResources::Vines_TopConnector,
		TerrainResources::Vines_TopConnectorConcave,
		TerrainResources::Vines_TopConnectorConcaveDeep,
		TerrainResources::Vines_TopConnectorConvex,
		TerrainResources::Vines_TopConnectorConvexDeep,
		TerrainResources::Vines_Bottom,
		TerrainResources::Vines_BottomLeft,
		TerrainResources::Vines_BottomRight,
		TerrainResources::Vines_BottomConnector,
		TerrainResources::Vines_Left,
		TerrainResources::Vines_LeftConnector,
		TerrainResources::Vines_Right,
		TerrainResources::Vines_RightConnector,
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
		InfillData(VinesTerrain::FillColor, false, true)))
{
}

VinesTerrain::~VinesTerrain()
{
}
