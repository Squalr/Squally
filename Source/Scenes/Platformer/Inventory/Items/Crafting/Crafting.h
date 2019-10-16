#pragma once

#include "Engine/Inventory/Item.h"

class Crafting : public Item
{
public:
protected:
	Crafting(CurrencyInventory* cost);
	~Crafting();

private:
	typedef Item super;
};
