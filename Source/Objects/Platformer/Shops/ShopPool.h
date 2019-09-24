#pragma once

#include "Engine/Inventory/ItemPool.h"

class CardPool;
class Item;

class ShopPool : public ItemPool
{
public:
	Item* getItemFromPool();

protected:
	ShopPool(cocos2d::ValueMap& properties, std::string poolName, CardPool* cardPool);
	~ShopPool();

private:
	typedef ItemPool super;

	CardPool* cardPool;
};
