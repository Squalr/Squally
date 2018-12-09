#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class CastleTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeCastle;

private:
	CastleTerrainDeserializer();
	~CastleTerrainDeserializer();

	static CastleTerrainDeserializer* instance;
};
