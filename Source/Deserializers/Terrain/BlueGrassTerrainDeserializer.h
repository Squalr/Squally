#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class BlueGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static BlueGrassTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeBlueGrass;

private:
	typedef TerrainDeserializer super;

	BlueGrassTerrainDeserializer();
	~BlueGrassTerrainDeserializer();
};
