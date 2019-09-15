#pragma once

#include "Engine/Maps/GameObject.h"

class Item;

class ChestPool : public GameObject
{
public:
	std::vector<Item*> getItemsFromPool();
	Item* getItemFromPool();

protected:
	ChestPool(cocos2d::ValueMap& properties, std::string poolName, int minItems, int maxItems);
	~ChestPool();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void addItemToPool(Item* item, float weight);

private:
	typedef GameObject super;

	void calculateWeightSum();

	cocos2d::Node* itemsNode;

	std::string poolName;
	std::vector<std::tuple<Item*, float>> itemPool;
	float weightSum;
	int minItems;
	int maxItems;
};
