#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Mace : public Weapon
{
public:
protected:
	Mace(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Mace();

private:
	typedef Weapon super;
};
