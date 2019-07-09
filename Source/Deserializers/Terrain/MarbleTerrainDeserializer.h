#pragma once

#include "Engine/Deserializers/TerrainDeserializer.h"

class MarbleTerrainDeserializer : public TerrainDeserializer
{
public:
	static MarbleTerrainDeserializer* create();

	static const std::string MapKeyTerrainTypeMarble;

private:
	typedef TerrainDeserializer super;
	
	MarbleTerrainDeserializer();
	~MarbleTerrainDeserializer();
};
