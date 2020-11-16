#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class Gear : public Equipable
{
public:

protected:
	Gear(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Gear();

private:
	typedef Equipable super;
};
