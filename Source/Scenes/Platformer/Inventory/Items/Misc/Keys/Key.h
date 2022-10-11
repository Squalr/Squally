#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class Key : public Misc
{
public:
protected:
	Key(CurrencyInventory* cost, ItemMeta itemMeta);
	virtual ~Key();

private:
	typedef Misc super;
};
