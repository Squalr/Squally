#include "LeafTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string LeafTerrain::MapKeyTerrainTypeLeaf = "leaf";

LeafTerrain* LeafTerrain::create(ValueMap& initProperties)
{
	LeafTerrain* instance = new LeafTerrain(initProperties);

	instance->autorelease();

	return instance;
}

LeafTerrain::LeafTerrain(ValueMap& initProperties) : super(
	initProperties,
	TerrainObject::TerrainData(
		0.5f,
		LeafTerrain::MapKeyTerrainTypeLeaf,
		TerrainResources::Leaf_LeafTexture,
		TerrainResources::Leaf_Leaf,
		TerrainResources::Leaf_LeafTopLeft,
		TerrainResources::Leaf_LeafTopRight,
		TerrainResources::Leaf_LeafBottom,
		TerrainResources::Leaf_LeafBottomLeft,
		TerrainResources::Leaf_LeafBottomRight,
		TerrainResources::Leaf_LeafLeft,
		TerrainResources::Leaf_LeafRight,
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2(-16.0f, 0.0f),
		cocos2d::Vec2(16.0f, 0.0f),
		cocos2d::Vec2::ZERO,
		cocos2d::Vec2::ZERO,
		Color4B(11, 30, 39, 255)))
{
}

LeafTerrain::~LeafTerrain()
{
}
