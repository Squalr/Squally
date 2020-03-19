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

protected:
	PlatformerItemDeserializer();
	virtual ~PlatformerItemDeserializer();

	void initializeListeners() override;

private:
	typedef GlobalNode super;

	void registerItem(const std::string& key, const std::function<Item*()>& item);

	std::map<std::string, std::function<Item*()>> deserializers;

	static PlatformerItemDeserializer* instance;
};
