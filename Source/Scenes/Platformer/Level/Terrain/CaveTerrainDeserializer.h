#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class CaveTerrainDeserializer : public TerrainDeserializer
{
public:
	static CaveTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeCave;

private:
	typedef TerrainDeserializer super;

	CaveTerrainDeserializer();
	~CaveTerrainDeserializer();
};
