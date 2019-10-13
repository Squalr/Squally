#pragma once

#include "Engine/Inventory/ItemPool.h"

class MinMaxPool;
class Item;

class ShopPool : public ItemPool
{
public:

protected:
	ShopPool(cocos2d::ValueMap& properties, std::string poolName, MinMaxPool* priorityPool);
	~ShopPool();

	Item* getItemFromPool(bool removeSampledItem) override;

private:
	typedef ItemPool super;

	MinMaxPool* priorityPool;

	cocos2d::Node* priorityPoolItemsNode;
};
