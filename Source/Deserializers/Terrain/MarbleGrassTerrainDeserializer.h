#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class MarbleGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static MarbleGrassTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeMarbleGrass;

private:
	typedef TerrainDeserializer super;
	
	MarbleGrassTerrainDeserializer();
	~MarbleGrassTerrainDeserializer();
};
