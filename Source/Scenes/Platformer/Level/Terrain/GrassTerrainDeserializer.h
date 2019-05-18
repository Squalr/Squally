#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class GrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeGrass;

private:
	typedef TerrainDeserializer super;
	GrassTerrainDeserializer();
	~GrassTerrainDeserializer();

	static GrassTerrainDeserializer* instance;
};
