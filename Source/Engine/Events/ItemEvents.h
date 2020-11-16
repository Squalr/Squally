#pragma once
#include <functional>
#include <string>
#include <vector>

class Item;
class Inventory;

class ItemEvents
{
public:
	static const std::string EventRequestItemFromPoolPrefix;

	struct ItemRequestArgs
	{
		std::string poolName;
		std::vector<Inventory*> inventories;
		std::function<void(Item*)> callback;

		ItemRequestArgs(std::string poolName, std::vector<Inventory*> inventories, std::function<void(Item*)> callback) : poolName(poolName), inventories(inventories), callback(callback)
		{
		}
	};

	static void TriggerRequestItem(ItemRequestArgs args);
};
