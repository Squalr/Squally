#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class DryTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeDry;

private:
	typedef TerrainDeserializer super;
	DryTerrainDeserializer();
	~DryTerrainDeserializer();

	static DryTerrainDeserializer* instance;
};
