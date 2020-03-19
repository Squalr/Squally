#include "TrailTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/TrailTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TrailTerrain::MapKey = "trail";

TrailTerrain* TrailTerrain::create(ValueMap& properties)
{
	TrailTerrain* instance = new TrailTerrain(properties);

	instance->autorelease();

	return instance;
}

TrailTerrain::TrailTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap& properties) { return TrailTexture::create(this->transformPropertiesForTexture(properties)); },
		0.5f,
		TrailTerrain::MapKey,
		TextureResources::TrailTexture,
		TerrainResources::Trail_Top,
		TerrainResources::Trail_TopLeft,
		TerrainResources::Trail_TopRight,
		TerrainResources::Trail_TopConnector,
		TerrainResources::Trail_TopConnectorConcave,
		TerrainResources::Trail_TopConnectorConcaveDeep,
		TerrainResources::Trail_TopConnectorConvex,
		TerrainResources::Trail_TopConnectorConvexDeep,
		TerrainResources::Trail_Bottom,
		TerrainResources::Trail_BottomLeft,
		TerrainResources::Trail_BottomRight,
		TerrainResources::Trail_BottomConnector,
		TerrainResources::Trail_Left,
		TerrainResources::Trail_LeftConnector,
		TerrainResources::Trail_Right,
		TerrainResources::Trail_RightConnector,
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
		Color4B(11, 30, 39, 255)))
{
}

TrailTerrain::~TrailTerrain()
{
}
