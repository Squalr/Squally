#pragma once

#include "Engine/Maps/GameObject.h"

class Item;
class ItemChance;

class ItemPool : public GameObject
{
public:

protected:
	ItemPool(const cocos2d::ValueMap& properties, std::string poolName = "");
	ItemPool(std::string poolName = "");
	~ItemPool();

	void initializeListeners() override;

	int getPoolSize();
	virtual Item* getItemFromPool(bool removeSampledItem);
	virtual Item* getItemFromPoolGuaranteed(bool removeSampledItem);
	virtual std::vector<Item*> getItemsFromPool(int count, bool removeSampledItems);
	virtual std::vector<Item*> getItemsFromPoolGuaranteed(int count, bool removeSampledItems);
	void addItemToPool(ItemChance* itemChance);
	void removeItemFromPool(ItemChance* itemChance);
	
	std::vector<ItemChance*> itemPool;

private:
	typedef GameObject super;

	struct ProbabilityData
	{
		ItemChance* itemChance;
		float probability;

		ProbabilityData(ItemChance* itemChance, float probability) : itemChance(itemChance), probability(probability) { }
	};

	cocos2d::Node* itemsNode;
	std::string poolName;

	std::vector<ProbabilityData> probabilityCache;
	float probabilitySum;
	bool cacheDirty;
};
