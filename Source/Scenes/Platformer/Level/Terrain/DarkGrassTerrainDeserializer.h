#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class DarkGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static DarkGrassTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeDarkGrass;

private:
	typedef TerrainDeserializer super;
	
	DarkGrassTerrainDeserializer();
	~DarkGrassTerrainDeserializer();
};
