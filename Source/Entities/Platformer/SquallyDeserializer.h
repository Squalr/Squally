#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"

class SquallyDeserializer : public PlatformerEntityDeserializer
{
public:
	static void registerGlobalNode();

private:
	SquallyDeserializer();
	~SquallyDeserializer();

	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args);

	static SquallyDeserializer* instance;
};
