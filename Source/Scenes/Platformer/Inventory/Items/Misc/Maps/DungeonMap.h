#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class DungeonMap : public Misc
{
public:
protected:
	DungeonMap(CurrencyInventory* cost, ItemMeta itemMeta);
	virtual ~DungeonMap();

private:
	typedef Misc super;
};
