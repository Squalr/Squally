#include "LeafTerrainDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string LeafTerrainDeserializer::MapKeyTerrainTypeLeaf = "leaf";

LeafTerrainDeserializer* LeafTerrainDeserializer::create()
{
	LeafTerrainDeserializer* instance = new LeafTerrainDeserializer();

	instance->autorelease();

	return instance;
}

LeafTerrainDeserializer::LeafTerrainDeserializer() : TerrainDeserializer(
	TerrainObject::TerrainData(
		0.5f,
		LeafTerrainDeserializer::MapKeyTerrainTypeLeaf,
		TerrainResources::Leaf_LeafTexture,
		TerrainResources::Leaf_Leaf,
		TerrainResources::Leaf_LeafTopLeft,
		TerrainResources::Leaf_LeafTopRight,
		TerrainResources::Leaf_LeafBottom,
		TerrainResources::Leaf_LeafBottomLeft,
		TerrainResources::Leaf_LeafBottomRight,
		TerrainResources::Leaf_LeafLeft,
		TerrainResources::Leaf_LeafRight,
		Color4B(11, 30, 39, 255)))
{
}

LeafTerrainDeserializer::~LeafTerrainDeserializer()
{
}
