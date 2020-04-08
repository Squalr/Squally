#include "MarbleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/MarbleTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MarbleTerrain::MapKey = "marble";

MarbleTerrain* MarbleTerrain::create(ValueMap& properties)
{
	MarbleTerrain* instance = new MarbleTerrain(properties);

	instance->autorelease();

	return instance;
}

MarbleTerrain::MarbleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return MarbleTexture::create(transformedProps);
		},
		0.5f,
		MarbleTerrain::MapKey,
		TextureResources::MarbleTexture,
		TerrainResources::Marble_Top,
		TerrainResources::Marble_TopLeft,
		TerrainResources::Marble_TopRight,
		TerrainResources::Marble_TopConnector,
		TerrainResources::Marble_TopConnectorConcave,
		TerrainResources::Marble_TopConnectorConcaveDeep,
		TerrainResources::Marble_TopConnectorConvex,
		TerrainResources::Marble_TopConnectorConvexDeep,
		TerrainResources::Marble_Bottom,
		TerrainResources::Marble_BottomLeft,
		TerrainResources::Marble_BottomRight,
		TerrainResources::Marble_BottomConnector,
		TerrainResources::Marble_Left,
		TerrainResources::Marble_LeftConnector,
		TerrainResources::Marble_Right,
		TerrainResources::Marble_RightConnector,
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

MarbleTerrain::~MarbleTerrain()
{
}
