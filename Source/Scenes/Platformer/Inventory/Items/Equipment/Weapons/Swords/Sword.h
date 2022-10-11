#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Sword : public Weapon
{
public:
	virtual std::string getWeaponAttackSound() override;
	virtual std::string getWeaponImpactSound() override;
	
protected:
	Sword(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Sword();

private:
	typedef Weapon super;
};
