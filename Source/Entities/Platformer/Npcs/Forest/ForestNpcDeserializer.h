#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

class ForestNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	ForestNpcDeserializer();
	~ForestNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static ForestNpcDeserializer* instance;
};
