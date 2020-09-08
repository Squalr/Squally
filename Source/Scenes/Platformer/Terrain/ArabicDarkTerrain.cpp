#include "ArabicDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ArabicDarkTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ArabicDarkTerrain::MapKey = "arabic-dark";
const Color4B ArabicDarkTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B ArabicDarkTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

ArabicDarkTerrain* ArabicDarkTerrain::create(ValueMap& properties)
{
	ArabicDarkTerrain* instance = new ArabicDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

ArabicDarkTerrain::ArabicDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return ArabicDarkTexture::create(transformedProps);
		},
		0.5f,
		ArabicDarkTerrain::MapKey,
		TextureResources::ArabicWebDarkTexture,
		TerrainResources::ArabicDark_Top,
		TerrainResources::ArabicDark_TopLeft,
		TerrainResources::ArabicDark_TopRight,
		TerrainResources::ArabicDark_TopConnector,
		TerrainResources::ArabicDark_TopConnectorConcave,
		TerrainResources::ArabicDark_TopConnectorConcaveDeep,
		TerrainResources::ArabicDark_TopConnectorConvex,
		TerrainResources::ArabicDark_TopConnectorConvexDeep,
		TerrainResources::ArabicDark_Bottom,
		TerrainResources::ArabicDark_BottomLeft,
		TerrainResources::ArabicDark_BottomRight,
		TerrainResources::ArabicDark_BottomConnector,
		TerrainResources::ArabicDark_Left,
		TerrainResources::ArabicDark_LeftConnector,
		TerrainResources::ArabicDark_Right,
		TerrainResources::ArabicDark_RightConnector,
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
		InfillData(ArabicDarkTerrain::FillColor, false, true, true)))
{
}

ArabicDarkTerrain::~ArabicDarkTerrain()
{
}
