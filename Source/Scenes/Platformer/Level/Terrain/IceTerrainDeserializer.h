#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class IceTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeIce;

private:
	typedef TerrainDeserializer super;
	IceTerrainDeserializer();
	~IceTerrainDeserializer();

	static IceTerrainDeserializer* instance;
};
