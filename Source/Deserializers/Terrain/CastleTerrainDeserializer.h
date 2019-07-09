#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class CastleTerrainDeserializer : public TerrainDeserializer
{
public:
	static CastleTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeCastle;

private:
	typedef TerrainDeserializer super;
	
	CastleTerrainDeserializer();
	~CastleTerrainDeserializer();
};
