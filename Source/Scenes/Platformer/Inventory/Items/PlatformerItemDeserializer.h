#pragma once

#include "Engine/Events/InventoryEvents.h"
#include "Engine/GlobalNode.h"

class PlatformerItemDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(InventoryEvents::RequestItemDeserializationArgs* args);

	static PlatformerItemDeserializer* instance;
};
