#include "DryTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/DryTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DryTerrain::MapKey = "dry";
const Color4B DryTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B DryTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

DryTerrain* DryTerrain::create(ValueMap& properties)
{
	DryTerrain* instance = new DryTerrain(properties);

	instance->autorelease();

	return instance;
}

DryTerrain::DryTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return DryTexture::create(transformedProps);
		},
		0.5f,
		DryTerrain::MapKey,
		TextureResources::DryTexture,
		TerrainResources::Dry_Top,
		TerrainResources::Dry_TopLeft,
		TerrainResources::Dry_TopRight,
		TerrainResources::Dry_TopConnector,
		TerrainResources::Dry_TopConnectorConcave,
		TerrainResources::Dry_TopConnectorConcaveDeep,
		TerrainResources::Dry_TopConnectorConvex,
		TerrainResources::Dry_TopConnectorConvexDeep,
		TerrainResources::Dry_Bottom,
		TerrainResources::Dry_BottomLeft,
		TerrainResources::Dry_BottomRight,
		TerrainResources::Dry_BottomConnector,
		TerrainResources::Dry_Left,
		TerrainResources::Dry_LeftConnector,
		TerrainResources::Dry_Right,
		TerrainResources::Dry_RightConnector,
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
		InfillData(DryTerrain::FillColor, false, true)))
{
}

DryTerrain::~DryTerrain()
{
}
