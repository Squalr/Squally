#include "ArabicTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ArabicTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ArabicTerrain::MapKey = "arabic";
const Color4B ArabicTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B ArabicTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

ArabicTerrain* ArabicTerrain::create(ValueMap& properties)
{
	ArabicTerrain* instance = new ArabicTerrain(properties);

	instance->autorelease();

	return instance;
}

ArabicTerrain::ArabicTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return ArabicTexture::create(transformedProps);
		},
		0.5f,
		ArabicTerrain::MapKey,
		TextureResources::ArabicWebTexture,
		TerrainResources::Arabic_Top,
		TerrainResources::Arabic_TopLeft,
		TerrainResources::Arabic_TopRight,
		TerrainResources::Arabic_TopConnector,
		TerrainResources::Arabic_TopConnectorConcave,
		TerrainResources::Arabic_TopConnectorConcaveDeep,
		TerrainResources::Arabic_TopConnectorConvex,
		TerrainResources::Arabic_TopConnectorConvexDeep,
		TerrainResources::Arabic_Bottom,
		TerrainResources::Arabic_BottomLeft,
		TerrainResources::Arabic_BottomRight,
		TerrainResources::Arabic_BottomConnector,
		TerrainResources::Arabic_Left,
		TerrainResources::Arabic_LeftConnector,
		TerrainResources::Arabic_Right,
		TerrainResources::Arabic_RightConnector,
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
		InfillData(ArabicTerrain::FillColor, false, true, true)))
{
}

ArabicTerrain::~ArabicTerrain()
{
}
