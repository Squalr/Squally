#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class LeafTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeLeaf;

private:
	typedef TerrainDeserializer super;
	LeafTerrainDeserializer();
	~LeafTerrainDeserializer();

	static LeafTerrainDeserializer* instance;
};
