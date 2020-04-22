#pragma once

#include "Engine/Maps/GameObject.h"

class Item;
class ItemChance;
class Inventory;

// Defines a pool of items that can be randomly sampled.
class ItemPool : public GameObject
{
public:

protected:
	friend class MergePool;
	
	ItemPool(const cocos2d::ValueMap& properties, std::string poolName = "");
	ItemPool(std::string poolName = "");
	virtual ~ItemPool();

	void initializeListeners() override;

	int getPoolSize();
	virtual Item* getItemFromPool(bool removeSampledItem, std::vector<Inventory*> inventories);
	virtual Item* getItemFromPoolGuaranteed(bool removeSampledItem, std::vector<Inventory*> inventories);
	virtual std::vector<Item*> getItemsFromPool(int count, std::vector<Inventory*> inventories, bool removeSampledItems);
	virtual std::vector<Item*> getItemsFromPoolGuaranteed(int count, std::vector<Inventory*> inventories, bool removeSampledItems);
	void addItemToPool(ItemChance* itemChance);
	void removeItemFromPool(ItemChance* itemChance);
	void toggleDisableShuffle(bool disableShuffle);
	
	std::vector<ItemChance*> itemPool;
	std::string poolName;

private:
	typedef GameObject super;

	struct ProbabilityData
	{
		ItemChance* itemChance;
		float probability;

		ProbabilityData(ItemChance* itemChance, float probability) : itemChance(itemChance), probability(probability) { }
	};

	void shuffleItems();

	cocos2d::Node* itemsNode;

	std::vector<ProbabilityData> probabilityCache;
	float probabilitySum;
	bool disableShuffle;
	bool cacheDirty;
};
