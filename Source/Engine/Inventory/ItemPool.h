#pragma once

#include "Engine/Maps/GameObject.h"

class Item;

class ItemPool : public GameObject
{
public:

protected:
	ItemPool(const cocos2d::ValueMap& properties, std::string poolName = "");
	ItemPool(std::string poolName = "");
	~ItemPool();

	void initializeListeners() override;

	virtual Item* getItemFromPool(bool removeSampledItem);
	virtual std::vector<Item*> getItemsFromPool(int count, bool removeSampledItems);
	void addItemToPool(Item* item, float weight);
	void removeItemFromPool(Item* item);
	
	std::vector<std::tuple<Item*, float>> itemPool;

private:
	typedef GameObject super;

	void calculateWeightSum();

	cocos2d::Node* itemsNode;

	std::string poolName;
	float weightSum;
};
