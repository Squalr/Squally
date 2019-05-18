#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class DryGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeDryGrass;

private:
	typedef TerrainDeserializer super;
	DryGrassTerrainDeserializer();
	~DryGrassTerrainDeserializer();

	static DryGrassTerrainDeserializer* instance;
};
