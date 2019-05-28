#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class MarbleTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeMarble;

private:
	typedef TerrainDeserializer super;
	MarbleTerrainDeserializer();
	~MarbleTerrainDeserializer();

	static MarbleTerrainDeserializer* instance;
};
