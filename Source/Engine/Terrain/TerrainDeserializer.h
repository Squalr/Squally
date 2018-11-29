#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/Utils/MPE_fastpoly2tri.h"

using namespace cocos2d;

class TerrainDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	TerrainDeserializer();
	~TerrainDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static TerrainDeserializer* instance;
};
