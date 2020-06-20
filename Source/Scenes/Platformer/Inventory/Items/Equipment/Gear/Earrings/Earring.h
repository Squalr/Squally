#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class LocalizedString;

class Earring : public Gear
{
public:
protected:
	Earring(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Earring();

private:
	typedef Gear super;
};
