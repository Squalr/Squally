#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class TrailTerrainDeserializer : public TerrainDeserializer
{
public:
	static TrailTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeTrail;

private:
	typedef TerrainDeserializer super;

	TrailTerrainDeserializer();
	~TrailTerrainDeserializer();
};
