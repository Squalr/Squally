#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class CollectableItem : public Item
{
public:

protected:
	CollectableItem(CurrencyInventory* cost);
	~CollectableItem();

private:
	typedef Item super;
};
