#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class CaveTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeCave;

private:
	typedef TerrainDeserializer super;
	CaveTerrainDeserializer();
	~CaveTerrainDeserializer();

	static CaveTerrainDeserializer* instance;
};
