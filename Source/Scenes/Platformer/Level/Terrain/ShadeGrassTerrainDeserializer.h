#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class ShadeGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeShadeGrass;

private:
	typedef TerrainDeserializer super;
	ShadeGrassTerrainDeserializer();
	~ShadeGrassTerrainDeserializer();

	static ShadeGrassTerrainDeserializer* instance;
};
