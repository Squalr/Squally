#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

class SnowNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	SnowNpcDeserializer();
	~SnowNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static SnowNpcDeserializer* instance;
};
