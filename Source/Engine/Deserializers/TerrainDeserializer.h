#pragma once

#include "Engine/Deserializers/ObjectDeserializer.h"
#include "Engine/Terrain/TerrainObject.h"

class TerrainDeserializer : public ObjectDeserializer
{
public:
	static std::string MapKeyTerrainType;

protected:
	TerrainDeserializer(TerrainObject::TerrainData terrainData);
	virtual ~TerrainDeserializer();

private:
	typedef ObjectDeserializer super;

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args);

	TerrainObject::TerrainData terrainData;
};
