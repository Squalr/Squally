#include "GrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/GrassTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string GrassTerrain::MapKey = "grass";
const Color4B GrassTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B GrassTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

GrassTerrain* GrassTerrain::create(ValueMap& properties)
{
	GrassTerrain* instance = new GrassTerrain(properties);

	instance->autorelease();

	return instance;
}

GrassTerrain::GrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return GrassTexture::create(transformedProps);
		},
		0.5f,
		GrassTerrain::MapKey,
		TextureResources::GrassTexture,
		TerrainResources::Grass_Top,
		TerrainResources::Grass_TopLeft,
		TerrainResources::Grass_TopRight,
		TerrainResources::Grass_TopConnector,
		TerrainResources::Grass_TopConnectorConcave,
		TerrainResources::Grass_TopConnectorConcaveDeep,
		TerrainResources::Grass_TopConnectorConvex,
		TerrainResources::Grass_TopConnectorConvexDeep,
		TerrainResources::Grass_Bottom,
		TerrainResources::Grass_BottomLeft,
		TerrainResources::Grass_BottomRight,
		TerrainResources::Grass_BottomConnector,
		TerrainResources::Grass_Left,
		TerrainResources::Grass_LeftConnector,
		TerrainResources::Grass_Right,
		TerrainResources::Grass_RightConnector,
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
		InfillData(GrassTerrain::FillColor, false, true)))
{
}

GrassTerrain::~GrassTerrain()
{
}
