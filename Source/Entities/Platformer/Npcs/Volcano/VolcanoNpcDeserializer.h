#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

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
