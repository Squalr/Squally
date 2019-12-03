#pragma once

#include "Engine/Inventory/ItemPool.h"

class ItemPool;
class Item;

class MinMaxPool : public ItemPool
{
public:
	Item* getItem();
	std::vector<Item*> getItems();

	enum class SampleMethod
	{
		// The max number of items given are based on the provided min and max. Warps probabilites in favor of common items.
		// Ie a min-max pool with a min of 1 and max of 3, a limit of 1-3 is decided in advance. If this limit is 1, a common item may be given out,
		// and no rare items will even have the chance to roll. In addition, the minimum is NOT enforced, so no items may be given at all.
		Random,

		// True random sampling, but voiolates everything the min-max pool stands for. This is a testament to my terrible game design and forsight.
		Unbounded,

		// Guaranteed to get between min and max items. Warps probabilites in favor of rare items for small pools.
		// Ie a min-max pool with a min of 2 and max of 2, with a common item and a rare item, will result in both items being given.
		Guarantee,
	};

protected:
	MinMaxPool(const cocos2d::ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, std::vector<MinMaxPool*> nestedPools = { });
	~MinMaxPool();

private:
	typedef ItemPool super;

	void calculateWeightSum();

	SampleMethod sampleMethod;
	std::vector<MinMaxPool*> nestedPools;

	int itemCount;
};
