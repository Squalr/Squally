#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class CavernsTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeCaverns;

private:
	typedef TerrainDeserializer super;
	CavernsTerrainDeserializer();
	~CavernsTerrainDeserializer();

	static CavernsTerrainDeserializer* instance;
};
