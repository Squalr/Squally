#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/Npcs/Ruins/RuinsNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class RuinsNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	RuinsNpcDeserializer();
	~RuinsNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static RuinsNpcDeserializer* instance;
};
