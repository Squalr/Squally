#pragma once

#include "Engine/Inventory/Item.h"

class Misc : public Item
{
public:
protected:
	Misc(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~Misc();

private:
	typedef Item super;
};
