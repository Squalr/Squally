#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class Item;

class RewardPool : public MinMaxPool
{
public:
	Item* getNextItem();
	
protected:
	RewardPool(cocos2d::ValueMap& properties, std::string poolName, std::vector<MinMaxPool*> nestedPools = { });
	virtual ~RewardPool();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;

	cocos2d::Node* itemsNode;
	std::vector<Item*> items;
};
