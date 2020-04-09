#include "CaveTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/CaveTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string CaveTerrain::MapKey = "cave";

CaveTerrain* CaveTerrain::create(ValueMap& properties)
{
	CaveTerrain* instance = new CaveTerrain(properties);

	instance->autorelease();

	return instance;
}

CaveTerrain::CaveTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return CaveTexture::create(transformedProps);
		},
		0.5f,
		CaveTerrain::MapKey,
		TextureResources::CaveTexture,
		TerrainResources::Cave_Top,
		TerrainResources::Cave_TopLeft,
		TerrainResources::Cave_TopRight,
		TerrainResources::Cave_TopConnector,
		TerrainResources::Cave_TopConnectorConcave,
		TerrainResources::Cave_TopConnectorConcaveDeep,
		TerrainResources::Cave_TopConnectorConvex,
		TerrainResources::Cave_TopConnectorConvexDeep,
		TerrainResources::Cave_Bottom,
		TerrainResources::Cave_BottomLeft,
		TerrainResources::Cave_BottomRight,
		TerrainResources::Cave_BottomConnector,
		TerrainResources::Cave_Left,
		TerrainResources::Cave_LeftConnector,
		TerrainResources::Cave_Right,
		TerrainResources::Cave_RightConnector,
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

CaveTerrain::~CaveTerrain()
{
}
