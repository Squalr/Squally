#include "ShadeGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/ShadeGrassTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string ShadeGrassTerrain::MapKey = "shade-grass";
const Color4B ShadeGrassTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B ShadeGrassTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

ShadeGrassTerrain* ShadeGrassTerrain::create(ValueMap& properties)
{
	ShadeGrassTerrain* instance = new ShadeGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

ShadeGrassTerrain::ShadeGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return ShadeGrassTexture::create(transformedProps);
		},
		0.5f,
		ShadeGrassTerrain::MapKey,
		TextureResources::ShadeGrassTexture,
		TerrainResources::ShadeGrass_Top,
		TerrainResources::ShadeGrass_TopLeft,
		TerrainResources::ShadeGrass_TopRight,
		TerrainResources::ShadeGrass_TopConnector,
		TerrainResources::ShadeGrass_TopConnectorConcave,
		TerrainResources::ShadeGrass_TopConnectorConcaveDeep,
		TerrainResources::ShadeGrass_TopConnectorConvex,
		TerrainResources::ShadeGrass_TopConnectorConvexDeep,
		TerrainResources::ShadeGrass_Bottom,
		TerrainResources::ShadeGrass_BottomLeft,
		TerrainResources::ShadeGrass_BottomRight,
		TerrainResources::ShadeGrass_BottomConnector,
		TerrainResources::ShadeGrass_Left,
		TerrainResources::ShadeGrass_LeftConnector,
		TerrainResources::ShadeGrass_Right,
		TerrainResources::ShadeGrass_RightConnector,
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
		InfillData(ShadeGrassTerrain::FillColor, false, true)))
{
}

ShadeGrassTerrain::~ShadeGrassTerrain()
{
}
