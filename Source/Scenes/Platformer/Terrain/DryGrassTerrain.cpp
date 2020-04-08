#include "DryGrassTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/DryGrassTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string DryGrassTerrain::MapKey = "dry-grass";

DryGrassTerrain* DryGrassTerrain::create(ValueMap& properties)
{
	DryGrassTerrain* instance = new DryGrassTerrain(properties);

	instance->autorelease();

	return instance;
}

DryGrassTerrain::DryGrassTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return DryGrassTexture::create(transformedProps);
		},
		0.5f,
		DryGrassTerrain::MapKey,
		TextureResources::DryGrassTexture,
		TerrainResources::DryGrass_Top,
		TerrainResources::DryGrass_TopLeft,
		TerrainResources::DryGrass_TopRight,
		TerrainResources::DryGrass_TopConnector,
		TerrainResources::DryGrass_TopConnectorConcave,
		TerrainResources::DryGrass_TopConnectorConcaveDeep,
		TerrainResources::DryGrass_TopConnectorConvex,
		TerrainResources::DryGrass_TopConnectorConvexDeep,
		TerrainResources::DryGrass_Bottom,
		TerrainResources::DryGrass_BottomLeft,
		TerrainResources::DryGrass_BottomRight,
		TerrainResources::DryGrass_BottomConnector,
		TerrainResources::DryGrass_Left,
		TerrainResources::DryGrass_LeftConnector,
		TerrainResources::DryGrass_Right,
		TerrainResources::DryGrass_RightConnector,
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

DryGrassTerrain::~DryGrassTerrain()
{
}
