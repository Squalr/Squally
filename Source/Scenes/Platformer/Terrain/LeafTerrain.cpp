#include "LeafTerrain.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Textures/LeafTexture.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LeafTerrain::MapKey = "leaf";
const Color4B LeafTerrain::FillColor = Color4B(11, 30, 39, 255);
const Color4B LeafTerrain::MiniMapColor = Color4B(11, 30, 39, 255);

LeafTerrain* LeafTerrain::create(ValueMap& properties)
{
	LeafTerrain* instance = new LeafTerrain(properties);

	instance->autorelease();

	return instance;
}

LeafTerrain::LeafTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		[=](ValueMap props)
		{
			ValueMap transformedProps = this->transformPropertiesForTexture(props);
			
			return LeafTexture::create(transformedProps);
		},
		0.5f,
		LeafTerrain::MapKey,
		TextureResources::LeafTexture,
		TerrainResources::Leaf_Top,
		TerrainResources::Leaf_TopLeft,
		TerrainResources::Leaf_TopRight,
		TerrainResources::Leaf_TopConnector,
		TerrainResources::Leaf_TopConnectorConcave,
		TerrainResources::Leaf_TopConnectorConcaveDeep,
		TerrainResources::Leaf_TopConnectorConvex,
		TerrainResources::Leaf_TopConnectorConvexDeep,
		TerrainResources::Leaf_Bottom,
		TerrainResources::Leaf_BottomLeft,
		TerrainResources::Leaf_BottomRight,
		TerrainResources::Leaf_BottomConnector,
		TerrainResources::Leaf_Left,
		TerrainResources::Leaf_LeftConnector,
		TerrainResources::Leaf_Right,
		TerrainResources::Leaf_RightConnector,
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
		InfillData(LeafTerrain::FillColor, false, true)))
{
}

LeafTerrain::~LeafTerrain()
{
}
