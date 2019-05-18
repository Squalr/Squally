#pragma once

#include "Engine/Terrain/TerrainDeserializer.h"

class JungleTerrainDeserializer : public TerrainDeserializer
{
public:
	static void registerGlobalNode();

	static const std::string MapKeyTerrainTypeJungle;

private:
	typedef TerrainDeserializer super;
	JungleTerrainDeserializer();
	~JungleTerrainDeserializer();

	static JungleTerrainDeserializer* instance;
};
