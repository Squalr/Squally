#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Bow : public Weapon
{
public:
protected:
	Bow(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Bow();

private:
	typedef Weapon super;
};
