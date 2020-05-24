#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class Item;

class ShopPool : public MinMaxPool
{
public:
	Item* getNextItem();
	
protected:
	ShopPool(cocos2d::ValueMap& properties, std::string poolName, std::vector<MinMaxPool*> nestedPools = { });
	virtual ~ShopPool();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MinMaxPool super;

	cocos2d::Node* itemsNode;
	std::vector<Item*> items;
};
