#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Wand : public Weapon
{
public:
	virtual std::string getWeaponAttackSound() override;
	virtual std::string getWeaponImpactSound() override;
	
protected:
	Wand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Wand();

private:
	typedef Weapon super;
};
