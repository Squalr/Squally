#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class IceTerrainDeserializer : public TerrainDeserializer
{
public:
	static IceTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeIce;

private:
	typedef TerrainDeserializer super;
	
	IceTerrainDeserializer();
	~IceTerrainDeserializer();
};
