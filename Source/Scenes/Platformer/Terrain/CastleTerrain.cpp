#include "CastleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/CastleTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CastleTerrain::MapKey = "castle";

CastleTerrain* CastleTerrain::create(ValueMap& properties)
{
	CastleTerrain* instance = new CastleTerrain(properties);

	instance->autorelease();

	return instance;
}

CastleTerrain::CastleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return CastleTexture::create(transformedProps);
		},
		0.5f,
		CastleTerrain::MapKey,
		TextureResources::CastleTexture,
		TerrainResources::Castle_Top,
		TerrainResources::Castle_TopLeft,
		TerrainResources::Castle_TopRight,
		TerrainResources::Castle_TopConnector,
		TerrainResources::Castle_TopConnectorConcave,
		TerrainResources::Castle_TopConnectorConcaveDeep,
		TerrainResources::Castle_TopConnectorConvex,
		TerrainResources::Castle_TopConnectorConvexDeep,
		TerrainResources::Castle_Bottom,
		TerrainResources::Castle_BottomLeft,
		TerrainResources::Castle_BottomRight,
		TerrainResources::Castle_BottomConnector,
		TerrainResources::Castle_Left,
		TerrainResources::Castle_LeftConnector,
		TerrainResources::Castle_Right,
		TerrainResources::Castle_RightConnector,
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
		Vec2(0.0f, 6.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 16.0f),
		// TopConnectorConvex
		Vec2(0.0f, -6.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -12.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

CastleTerrain::~CastleTerrain()
{
}
