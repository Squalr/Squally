#pragma once

#include "Engine/Inventory/ItemPool.h"

class CardPool;
class Item;

class ChestPool : public ItemPool
{
public:
	std::vector<Item*> getChestItems();

protected:
	ChestPool(cocos2d::ValueMap& properties, std::string poolName, int minItems, int maxItems, CardPool* cardPool);
	~ChestPool();

private:
	typedef ItemPool super;

	void calculateWeightSum();

	int minItems;
	int maxItems;
};
