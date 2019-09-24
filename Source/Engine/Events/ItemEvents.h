#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

class Item;

class ItemEvents
{
public:
	static const std::string EventRequestItemFromPoolPrefix;

	struct ItemRequestArgs
	{
		std::string poolName;
		std::function<void(Item*)> callback;

		ItemRequestArgs(std::string poolName, std::function<void(Item*)> callback) : poolName(poolName), callback(callback)
		{
		}
	};

	static void TriggerRequestItem(ItemRequestArgs args);
};
