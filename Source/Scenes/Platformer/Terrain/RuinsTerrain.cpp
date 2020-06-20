#include "RuinsTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/RuinsTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsTerrain::MapKey = "ruins";

RuinsTerrain* RuinsTerrain::create(ValueMap& properties)
{
	RuinsTerrain* instance = new RuinsTerrain(properties);

	instance->autorelease();

	return instance;
}

RuinsTerrain::RuinsTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return RuinsTexture::create(transformedProps);
		},
		0.5f,
		RuinsTerrain::MapKey,
		TextureResources::RuinsTexture,
		TerrainResources::Ruins_Top,
		TerrainResources::Ruins_TopLeft,
		TerrainResources::Ruins_TopRight,
		TerrainResources::Ruins_TopConnector,
		TerrainResources::Ruins_TopConnectorConcave,
		TerrainResources::Ruins_TopConnectorConcaveDeep,
		TerrainResources::Ruins_TopConnectorConvex,
		TerrainResources::Ruins_TopConnectorConvexDeep,
		TerrainResources::Ruins_Bottom,
		TerrainResources::Ruins_BottomLeft,
		TerrainResources::Ruins_BottomRight,
		TerrainResources::Ruins_BottomConnector,
		TerrainResources::Ruins_Left,
		TerrainResources::Ruins_LeftConnector,
		TerrainResources::Ruins_Right,
		TerrainResources::Ruins_RightConnector,
		// Top
		Vec2(0.0f, -16.0f),
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2(0.0f, -2.0f),
		// TopRight
		Vec2(0.0f, -2.0f),
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
		Vec2(0.0f, -6.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -8.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

RuinsTerrain::~RuinsTerrain()
{
}
