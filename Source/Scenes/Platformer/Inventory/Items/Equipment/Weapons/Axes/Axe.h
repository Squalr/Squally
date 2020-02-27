#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Axe : public Weapon
{
public:
protected:
	Axe(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Axe();

private:
	typedef Weapon super;
};
