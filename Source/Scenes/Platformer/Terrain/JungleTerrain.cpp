#include "JungleTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/JungleTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string JungleTerrain::MapKey = "jungle";
const Color4B JungleTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B JungleTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

JungleTerrain* JungleTerrain::create(ValueMap& properties)
{
	JungleTerrain* instance = new JungleTerrain(properties);

	instance->autorelease();

	return instance;
}

JungleTerrain::JungleTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return JungleTexture::create(transformedProps);
		},
		0.5f,
		JungleTerrain::MapKey,
		TextureResources::JungleTexture,
		TerrainResources::Jungle_Top,
		TerrainResources::Jungle_TopLeft,
		TerrainResources::Jungle_TopRight,
		TerrainResources::Jungle_TopConnector,
		TerrainResources::Jungle_TopConnectorConcave,
		TerrainResources::Jungle_TopConnectorConcaveDeep,
		TerrainResources::Jungle_TopConnectorConvex,
		TerrainResources::Jungle_TopConnectorConvexDeep,
		TerrainResources::Jungle_Bottom,
		TerrainResources::Jungle_BottomLeft,
		TerrainResources::Jungle_BottomRight,
		TerrainResources::Jungle_BottomConnector,
		TerrainResources::Jungle_Left,
		TerrainResources::Jungle_LeftConnector,
		TerrainResources::Jungle_Right,
		TerrainResources::Jungle_RightConnector,
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
		InfillData(JungleTerrain::FillColor, false, true, true)))
{
}

JungleTerrain::~JungleTerrain()
{
}
