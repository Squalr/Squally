#pragma once

#include "Engine/Inventory/Item.h"

class Crafting : public Item
{
public:
protected:
	Crafting(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	~Crafting();

private:
	typedef Item super;
};
