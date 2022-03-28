#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Bow : public Weapon
{
public:
	virtual std::string getWeaponAttackSound() override;
	virtual std::string getWeaponImpactSound() override;

protected:
	Bow(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Bow();

private:
	typedef Weapon super;
};
