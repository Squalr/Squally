#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

class MechNpcDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	MechNpcDeserializer();
	~MechNpcDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static MechNpcDeserializer* instance;
};
