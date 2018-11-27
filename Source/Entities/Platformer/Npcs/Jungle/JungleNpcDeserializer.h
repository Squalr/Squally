#pragma once
#include "cocos2d.h"

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/Npcs/Jungle/JungleNpcs.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

using namespace cocos2d;

class JungleNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	JungleNpcDeserializer();
	~JungleNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static JungleNpcDeserializer* instance;
};
