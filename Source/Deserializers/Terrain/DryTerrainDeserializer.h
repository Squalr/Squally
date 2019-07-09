#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class DryTerrainDeserializer : public TerrainDeserializer
{
public:
	static DryTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeDry;

private:
	typedef TerrainDeserializer super;

	DryTerrainDeserializer();
	~DryTerrainDeserializer();
};
