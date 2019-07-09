#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class LeafTerrainDeserializer : public TerrainDeserializer
{
public:
	static LeafTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeLeaf;

private:
	typedef TerrainDeserializer super;

	LeafTerrainDeserializer();
	~LeafTerrainDeserializer();
};
