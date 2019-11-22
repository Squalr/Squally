#include "LeafTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string LeafTerrain::MapKeyTerrainType = "leaf";

LeafTerrain* LeafTerrain::create(ValueMap& properties)
{
	LeafTerrain* instance = new LeafTerrain(properties);

	instance->autorelease();

	return instance;
}

LeafTerrain::LeafTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		LeafTerrain::MapKeyTerrainType,
		TextureResources::LeafTexture,
		TerrainResources::Leaf_Leaf,
		TerrainResources::Leaf_LeafTopLeft,
		TerrainResources::Leaf_LeafTopRight,
		TerrainResources::Leaf_LeafBottom,
		TerrainResources::Leaf_LeafBottomLeft,
		TerrainResources::Leaf_LeafBottomRight,
		TerrainResources::Leaf_LeafLeft,
		TerrainResources::Leaf_LeafRight,
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
		Color4B(11, 30, 39, 255)))
{
}

LeafTerrain::~LeafTerrain()
{
}
