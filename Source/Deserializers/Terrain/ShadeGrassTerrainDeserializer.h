#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class ShadeGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static ShadeGrassTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeShadeGrass;

private:
	typedef TerrainDeserializer super;
	
	ShadeGrassTerrainDeserializer();
	~ShadeGrassTerrainDeserializer();
};
