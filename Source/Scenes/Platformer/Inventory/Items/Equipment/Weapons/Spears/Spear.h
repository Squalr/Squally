#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Spear : public Weapon
{
public:
protected:
	Spear(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Spear();

private:
	typedef Weapon super;
};
