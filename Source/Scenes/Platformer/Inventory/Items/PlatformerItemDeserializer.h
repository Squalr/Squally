#pragma once

#include "Engine/Events/InventoryEvents.h"
#include "Engine/GlobalNode.h"

class PlatformerItemDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

	static void onDeserializationRequest(InventoryEvents::RequestItemDeserializationArgs* args);

private:
	typedef GlobalNode super;
	void initializeListeners() override;

	static PlatformerItemDeserializer* instance;
};
