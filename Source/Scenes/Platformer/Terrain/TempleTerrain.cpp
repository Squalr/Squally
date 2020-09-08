#include "TempleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/TempleTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleTerrain::MapKey = "temple";
const Color4B TempleTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B TempleTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

TempleTerrain* TempleTerrain::create(ValueMap& properties)
{
	TempleTerrain* instance = new TempleTerrain(properties);

	instance->autorelease();

	return instance;
}

TempleTerrain::TempleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return TempleTexture::create(transformedProps);
		},
		0.5f,
		TempleTerrain::MapKey,
		TextureResources::TempleTexture,
		TerrainResources::Temple_Top,
		TerrainResources::Temple_TopLeft,
		TerrainResources::Temple_TopRight,
		TerrainResources::Temple_TopConnector,
		TerrainResources::Temple_TopConnectorConcave,
		TerrainResources::Temple_TopConnectorConcaveDeep,
		TerrainResources::Temple_TopConnectorConvex,
		TerrainResources::Temple_TopConnectorConvexDeep,
		TerrainResources::Temple_Bottom,
		TerrainResources::Temple_BottomLeft,
		TerrainResources::Temple_BottomRight,
		TerrainResources::Temple_BottomConnector,
		TerrainResources::Temple_Left,
		TerrainResources::Temple_LeftConnector,
		TerrainResources::Temple_Right,
		TerrainResources::Temple_RightConnector,
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
		Vec2(0.0f, -6.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -8.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		InfillData(TempleTerrain::FillColor, false, true, true)))
{
}

TempleTerrain::~TempleTerrain()
{
}
