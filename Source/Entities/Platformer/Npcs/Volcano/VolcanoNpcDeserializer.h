#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/Npcs/Volcano/VolcanoNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class VolcanoNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	VolcanoNpcDeserializer();
	~VolcanoNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static VolcanoNpcDeserializer* instance;
};
