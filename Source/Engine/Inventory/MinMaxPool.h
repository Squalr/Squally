#pragma once

#include "Engine/Inventory/ItemPool.h"

class ItemPool;
class Item;

class MinMaxPool : public ItemPool
{
public:
	Item* getItem();
	std::vector<Item*> getItems();

protected:
	MinMaxPool(const cocos2d::ValueMap& properties, std::string poolName, int minItems, int maxItems, MinMaxPool* nestedPool = nullptr);
	~MinMaxPool();

private:
	typedef ItemPool super;

	void calculateWeightSum();

	MinMaxPool* nestedPool;

	int itemCount;
};
