#include "LeafTerrainDeserializer.h"

#include "Engine/GlobalDirector.h"

#include "Resources/TerrainResources.h"

using namespace cocos2d;

const std::string LeafTerrainDeserializer::MapKeyTerrainTypeLeaf = "leaf";
LeafTerrainDeserializer* LeafTerrainDeserializer::instance = nullptr;

void LeafTerrainDeserializer::registerGlobalNode()
{
	if (LeafTerrainDeserializer::instance == nullptr)
	{
		LeafTerrainDeserializer::instance = new LeafTerrainDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(LeafTerrainDeserializer::instance);
	}
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
