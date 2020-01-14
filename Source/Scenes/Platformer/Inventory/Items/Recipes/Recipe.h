#pragma once

#include "Engine/Inventory/Item.h"

class Recipe : public Item
{
public:
	virtual Item* craft() = 0;
	virtual std::map<std::string, int> getReagents() = 0;
	
protected:
	Recipe(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~Recipe();

private:
	typedef Item super;
};
