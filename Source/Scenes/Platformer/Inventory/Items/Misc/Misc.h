#pragma once

#include "Engine/Inventory/Item.h"

class Misc : public Item
{
public:
protected:
	Misc(CurrencyInventory* cost);
	~Misc();

private:
	typedef Item super;
};
