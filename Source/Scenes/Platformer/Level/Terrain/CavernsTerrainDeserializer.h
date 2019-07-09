#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class CavernsTerrainDeserializer : public TerrainDeserializer
{
public:
	static CavernsTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeCaverns;

private:
	typedef TerrainDeserializer super;

	CavernsTerrainDeserializer();
	~CavernsTerrainDeserializer();
};
