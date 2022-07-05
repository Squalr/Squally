#include "MagmaTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/MagmaTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string MagmaTerrain::MapKey = "magma";
const Color4B MagmaTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B MagmaTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

MagmaTerrain* MagmaTerrain::create(ValueMap& properties)
{
	MagmaTerrain* instance = new MagmaTerrain(properties);

	instance->autorelease();

	return instance;
}

MagmaTerrain::MagmaTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return MagmaTexture::create(transformedProps);
		},
		0.5f,
		MagmaTerrain::MapKey,
		TextureResources::MagmaTexture,
		TerrainResources::Obsidean_Top,
		TerrainResources::Obsidean_TopLeft,
		TerrainResources::Obsidean_TopRight,
		TerrainResources::Obsidean_TopConnector,
		TerrainResources::Obsidean_TopConnectorConcave,
		TerrainResources::Obsidean_TopConnectorConcaveDeep,
		TerrainResources::Obsidean_TopConnectorConvex,
		TerrainResources::Obsidean_TopConnectorConvexDeep,
		TerrainResources::Obsidean_Bottom,
		TerrainResources::Obsidean_BottomLeft,
		TerrainResources::Obsidean_BottomRight,
		TerrainResources::Obsidean_BottomConnector,
		TerrainResources::Obsidean_Left,
		TerrainResources::Obsidean_LeftConnector,
		TerrainResources::Obsidean_Right,
		TerrainResources::Obsidean_RightConnector,
		// Top
		Vec2::ZERO,
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2(-20.0f, 0.0f),
		// TopRight
		Vec2(20.0f, 4.0f),
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
		InfillData(MagmaTerrain::FillColor, false, true)))
{
}

MagmaTerrain::~MagmaTerrain()
{
}
