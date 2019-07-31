#pragma once
#include <functional>
#include <string>

class CurrencyInventory;
class Inventory;
class Item;

class InventoryEvents
{
public:
	static const std::string EventRequestItemDeserialization;
	static const std::string EventInventoryInstanceChangedPrefix;
	static const std::string EventCurrencyInventoryInstanceChangedPrefix;

	struct RequestItemDeserializationArgs
	{
		std::string itemSerializationKey;
		std::function<void(Item*)> onItemDeserializedCallback;

		RequestItemDeserializationArgs(std::string itemSerializationKey, std::function<void(Item*)> onItemDeserializedCallback) : itemSerializationKey(itemSerializationKey), onItemDeserializedCallback(onItemDeserializedCallback) { }
	};

	struct InventoryInstanceChangedArgs
	{
		Inventory* instance;
		std::string inventorySaveKey;

		InventoryInstanceChangedArgs(Inventory* instance, std::string inventorySaveKey) : instance(instance), inventorySaveKey(inventorySaveKey) { }
	};

	struct CurrencyInventoryInstanceChangedArgs
	{
		CurrencyInventory* instance;
		std::string inventorySaveKey;

		CurrencyInventoryInstanceChangedArgs(CurrencyInventory* instance, std::string inventorySaveKey) : instance(instance), inventorySaveKey(inventorySaveKey) { }
	};

	static void TriggerRequestItemDeserialization(RequestItemDeserializationArgs args);
	static void TriggerInventoryInstanceChanged(InventoryInstanceChangedArgs args);
	static void TriggerCurrencyInventoryInstanceChanged(CurrencyInventoryInstanceChangedArgs args);
};
