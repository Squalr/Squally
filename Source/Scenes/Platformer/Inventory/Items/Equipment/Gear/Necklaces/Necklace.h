#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class LocalizedString;

class Necklace : public Gear
{
public:
protected:
	Necklace(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Necklace();

private:
	typedef Gear super;
};
