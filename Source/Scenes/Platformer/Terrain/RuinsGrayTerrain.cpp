#include "RuinsGrayTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/RuinsGrayTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string RuinsGrayTerrain::MapKey = "ruins-gray";
const Color4B RuinsGrayTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B RuinsGrayTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

RuinsGrayTerrain* RuinsGrayTerrain::create(ValueMap& properties)
{
	RuinsGrayTerrain* instance = new RuinsGrayTerrain(properties);

	instance->autorelease();

	return instance;
}

RuinsGrayTerrain::RuinsGrayTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return RuinsGrayTexture::create(transformedProps);
		},
		0.5f,
		RuinsGrayTerrain::MapKey,
		TextureResources::RuinsGrayTexture,
		TerrainResources::RuinsGray_Top,
		TerrainResources::RuinsGray_TopLeft,
		TerrainResources::RuinsGray_TopRight,
		TerrainResources::RuinsGray_TopConnector,
		TerrainResources::RuinsGray_TopConnectorConcave,
		TerrainResources::RuinsGray_TopConnectorConcaveDeep,
		TerrainResources::RuinsGray_TopConnectorConvex,
		TerrainResources::RuinsGray_TopConnectorConvexDeep,
		TerrainResources::RuinsGray_Bottom,
		TerrainResources::RuinsGray_BottomLeft,
		TerrainResources::RuinsGray_BottomRight,
		TerrainResources::RuinsGray_BottomConnector,
		TerrainResources::RuinsGray_Left,
		TerrainResources::RuinsGray_LeftConnector,
		TerrainResources::RuinsGray_Right,
		TerrainResources::RuinsGray_RightConnector,
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
		InfillData(RuinsGrayTerrain::FillColor, false, true, true)))
{
}

RuinsGrayTerrain::~RuinsGrayTerrain()
{
}
