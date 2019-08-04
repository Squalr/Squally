#pragma once

#include "Engine/Events/InventoryEvents.h"
#include "Engine/GlobalNode.h"

class Item;

class PlatformerItemDeserializer : public GlobalNode
{
public:
	static PlatformerItemDeserializer* getInstance();
	static void registerGlobalNode();

	void deserialize(InventoryEvents::RequestItemDeserializationArgs args);

private:
	typedef GlobalNode super;
	PlatformerItemDeserializer();
	~PlatformerItemDeserializer();
	void initializeListeners() override;

	std::map<std::string, std::function<Item*()>> deserializers;

	static PlatformerItemDeserializer* instance;
};
