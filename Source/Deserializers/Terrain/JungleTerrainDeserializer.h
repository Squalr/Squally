#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class JungleTerrainDeserializer : public TerrainDeserializer
{
public:
	static JungleTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeJungle;

private:
	typedef TerrainDeserializer super;
	
	JungleTerrainDeserializer();
	~JungleTerrainDeserializer();
};
