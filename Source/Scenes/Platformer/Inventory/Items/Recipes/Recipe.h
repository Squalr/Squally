#pragma once

#include "Engine/Inventory/Item.h"

class Recipe : public Item
{
public:
	virtual Item* craft() = 0;
	std::vector<std::tuple<Item*, int>> getReagents();
	
	Item* getCraftedItemRef();
	virtual std::string getCraftedItemIconResource() = 0;

protected:
	Recipe(CurrencyInventory* cost);
	virtual ~Recipe();

	virtual std::vector<std::tuple<Item*, int>> getReagentsInternal() = 0;

private:
	typedef Item super;

	Item* craftedItem;

	cocos2d::Node* reagentsNode;
	std::vector<std::tuple<Item*, int>> reagentsCache;
};
