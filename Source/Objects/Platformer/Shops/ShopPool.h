#pragma once

#include "Engine/Maps/GameObject.h"

class Item;

class ShopPool : public GameObject
{
public:
	Item* getItemFromPool();

protected:
	ShopPool(cocos2d::ValueMap& properties, std::string poolName);
	~ShopPool();
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
};
