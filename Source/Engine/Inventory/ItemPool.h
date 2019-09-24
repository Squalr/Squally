#pragma once

#include "Engine/Maps/GameObject.h"

class Item;

class ItemPool : public GameObject
{
public:

protected:
	ItemPool(const cocos2d::ValueMap&  properties, std::string poolName = "");
	ItemPool(std::string poolName = "");
	~ItemPool();

	void initializeListeners() override;

	virtual Item* getItemFromPool();
	std::vector<Item*> getItemsFromPool(int count);
	void addItemToPool(Item* item, float weight);
	void removeCardFromPool(Item* item);

private:
	typedef GameObject super;

	void calculateWeightSum();

	cocos2d::Node* itemsNode;

	std::string poolName;
	std::vector<std::tuple<Item*, float>> itemPool;
	float weightSum;
};
