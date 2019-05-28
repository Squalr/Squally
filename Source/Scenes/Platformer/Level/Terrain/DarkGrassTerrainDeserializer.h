#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class DarkGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeDarkGrass;

private:
	typedef TerrainDeserializer super;
	DarkGrassTerrainDeserializer();
	~DarkGrassTerrainDeserializer();

	static DarkGrassTerrainDeserializer* instance;
};
