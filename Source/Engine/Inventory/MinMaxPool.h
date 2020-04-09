#pragma once

#include "Engine/Inventory/ItemPool.h"

class ItemPool;
class Item;
class Inventory;

// Defines a pool of items that can be randomly sampled. Builds upon ItemPool by optionally allowing a min/max number of items to be given.
// Useful for drops, chests, rewards, etc.
class MinMaxPool : public ItemPool
{
public:
	Item* getItem(std::vector<Inventory*> inventories);
	std::vector<Item*> getItems(std::vector<Inventory*> inventories);

	enum class SampleMethod
	{
		// The max number of items given are based on the provided min and max. Warps probabilites in favor of common items.
		// Ie a min-max pool with a min of 1 and max of 3, a limit of 1-3 is decided in advance. From there, items are randomly sampled based on
		// their relative probabilities. In addition, the minimum is NOT enforced, so no items may be given at all.
		Random,

		// True random sampling, voliating the min and max of this pool. This exists to allow MinMaxPools to behave like ItemPools when convenient.
		Unbounded,

		// Guaranteed to get between min and max items. Warps probabilites in favor of rare items for small pools.
		// Ie a min-max pool with a min of 2 and max of 2, with a common item and a rare item, will result in both items being given.
		// With a min of 1 and max of 3, the number of items to give is decided in advance, and items are sampled based on relative probabilities.
		Guarantee,
	};

protected:
	MinMaxPool(const cocos2d::ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, std::vector<MinMaxPool*> nestedPools = { });
	virtual ~MinMaxPool();

private:
	typedef ItemPool super;

	void calculateWeightSum();

	SampleMethod sampleMethod;
	std::vector<MinMaxPool*> nestedPools;

	int itemCount;
};
