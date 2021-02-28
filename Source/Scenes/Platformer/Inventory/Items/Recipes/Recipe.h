#pragma once

#include "Engine/Inventory/Item.h"

class Recipe : public Item
{
public:
	virtual std::vector<Item*> craft() = 0;
	std::vector<std::tuple<Item*, int>> getReagents();
	
	std::vector<Item*>& getCraftedItemsRef();
	virtual std::string getCraftedItemIconResource() = 0;

protected:
	Recipe(CurrencyInventory* cost = nullptr);
	virtual ~Recipe();

	virtual std::vector<std::tuple<Item*, int>> getReagentsInternal() = 0;

private:
	typedef Item super;

	std::vector<Item*> craftedItems;

	cocos2d::Node* reagentsNode;
	std::vector<std::tuple<Item*, int>> reagentsCache;
};
