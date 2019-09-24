#pragma once

#include "Engine/Maps/GameObject.h"

class Item;

class ItemPool : public GameObject
{
public:
	Item* getItemFromPool();
	std::vector<Item*> getItemsFromPool(int count);

protected:
	ItemPool(const cocos2d::ValueMap&  properties, std::string poolName = "", ItemPool* priorityPool = nullptr);
	ItemPool(std::string poolName = "", ItemPool* priorityPool = nullptr);
	~ItemPool();

	void initializeListeners() override;

	void addItemToPool(Item* item, float weight);
	void removeCardFromPool(Item* item);

private:
	typedef GameObject super;

	void calculateWeightSum();

	cocos2d::Node* itemsNode;

	ItemPool* priorityPool;
	std::string poolName;
	std::vector<std::tuple<Item*, float>> itemPool;
	float weightSum;
};
