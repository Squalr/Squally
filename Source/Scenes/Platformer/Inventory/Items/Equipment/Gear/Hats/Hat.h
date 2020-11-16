#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class Hat : public Gear
{
public:

protected:
	Hat(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Hat();

private:
	typedef Gear super;
};
