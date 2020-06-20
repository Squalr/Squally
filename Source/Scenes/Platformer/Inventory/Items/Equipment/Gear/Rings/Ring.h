#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class LocalizedString;

class Ring : public Gear
{
public:
protected:
	Ring(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Ring();

private:
	typedef Gear super;
};
