#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Sword : public Weapon
{
public:
	std::string getWeaponAttackSound() override;
	
protected:
	Sword(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Sword();

private:
	typedef Weapon super;
};
