#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Terrain/TerrainObject.h"

using namespace cocos2d;

class TerrainDeserializer : public GlobalNode
{
public:
	static std::string MapKeyTerrainType;

protected:
	TerrainDeserializer(TerrainObject::TerrainData terrainData);
	~TerrainDeserializer();

private:
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	TerrainObject::TerrainData terrainData;

	static TerrainDeserializer* instance;
};
