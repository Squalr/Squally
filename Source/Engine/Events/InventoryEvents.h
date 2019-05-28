#pragma once
#include <functional>
#include <string>

class Inventory;
class Item;

class InventoryEvents
{
public:
	static const std::string EventRequestItemDeserialization;

	struct RequestItemDeserializationArgs
	{
		std::string itemSerializationKey;
		std::function<void(Item*)> onItemDeserializedCallback;

		RequestItemDeserializationArgs(std::string itemSerializationKey, std::function<void(Item*)> onItemDeserializedCallback) : itemSerializationKey(itemSerializationKey), onItemDeserializedCallback(onItemDeserializedCallback) { }
	};

	static void TriggerRequestItemDeserialization(RequestItemDeserializationArgs args);
};
