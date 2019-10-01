#pragma once

#include "Engine/Inventory/ItemPool.h"

class CardPool;
class Item;

class ShopPool : public ItemPool
{
public:

protected:
	ShopPool(cocos2d::ValueMap& properties, std::string poolName, CardPool* cardPool);
	~ShopPool();

	Item* getItemFromPool(bool removeSampledItem) override;

private:
	typedef ItemPool super;

	CardPool* cardPool;
};
