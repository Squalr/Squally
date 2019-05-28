#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class MarbleGrassTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeMarbleGrass;

private:
	typedef TerrainDeserializer super;
	MarbleGrassTerrainDeserializer();
	~MarbleGrassTerrainDeserializer();

	static MarbleGrassTerrainDeserializer* instance;
};
