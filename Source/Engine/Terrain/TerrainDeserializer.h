#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Terrain/TerrainObject.h"

class TerrainDeserializer : public GlobalNode
{
public:
	static std::string MapKeyTerrainType;

protected:
	TerrainDeserializer(TerrainObject::TerrainData terrainData);
	virtual ~TerrainDeserializer();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	TerrainObject::TerrainData terrainData;

	static TerrainDeserializer* instance;
};
