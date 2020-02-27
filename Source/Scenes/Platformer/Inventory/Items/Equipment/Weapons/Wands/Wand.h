#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Wand : public Weapon
{
public:
protected:
	Wand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Wand();

private:
	typedef Weapon super;
};
