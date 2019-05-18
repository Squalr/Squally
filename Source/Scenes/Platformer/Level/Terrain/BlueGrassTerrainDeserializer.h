#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class BlueGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeBlueGrass;

private:
	typedef TerrainDeserializer super;
	BlueGrassTerrainDeserializer();
	~BlueGrassTerrainDeserializer();

	static BlueGrassTerrainDeserializer* instance;
};
