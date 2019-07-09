#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class DryGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static DryGrassTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeDryGrass;

private:
	typedef TerrainDeserializer super;

	DryGrassTerrainDeserializer();
	~DryGrassTerrainDeserializer();
};
