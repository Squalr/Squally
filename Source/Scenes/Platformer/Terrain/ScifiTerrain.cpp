#include "ScifiTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ScifiDarkTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ScifiTerrain::MapKey = "scifi";
const Color4B ScifiTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B ScifiTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

ScifiTerrain* ScifiTerrain::create(ValueMap& properties)
{
	ScifiTerrain* instance = new ScifiTerrain(properties);

	instance->autorelease();

	return instance;
}

ScifiTerrain::ScifiTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return ScifiDarkTexture::create(transformedProps);
		},
		0.5f,
		ScifiTerrain::MapKey,
		TextureResources::ScifiDarkTexture,
		TerrainResources::Scifi_Top,
		TerrainResources::Scifi_TopLeft,
		TerrainResources::Scifi_TopRight,
		TerrainResources::Scifi_TopConnector,
		TerrainResources::Scifi_TopConnectorConcave,
		TerrainResources::Scifi_TopConnectorConcaveDeep,
		TerrainResources::Scifi_TopConnectorConvex,
		TerrainResources::Scifi_TopConnectorConvexDeep,
		TerrainResources::Scifi_Bottom,
		TerrainResources::Scifi_BottomLeft,
		TerrainResources::Scifi_BottomRight,
		TerrainResources::Scifi_BottomConnector,
		TerrainResources::Scifi_Left,
		TerrainResources::Scifi_LeftConnector,
		TerrainResources::Scifi_Right,
		TerrainResources::Scifi_RightConnector,
		// Top
		Vec2(0.0f, -8.0f),
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2(0.0f, 4.0f),
		// TopRight
		Vec2(0.0f, 4.0f),
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
		InfillData(ScifiTerrain::FillColor, false, true)))
{
}

ScifiTerrain::~ScifiTerrain()
{
}
