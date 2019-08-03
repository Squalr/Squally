#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class LocalizedString;

class Hat : public Gear
{
public:

protected:
	Hat(CurrencyInventory* cost, int defense);
	virtual ~Hat();

private:
	typedef Gear super;
};
