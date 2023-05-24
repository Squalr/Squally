#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

// Axes: Large damage variance, slow timeline speed, balanced hp/mp (favoring mp)
#define AXE_RANGE(tier) tier + 2 - tier / 3
#define AXE_DAMAGE_MIN(tier) BASE_SCALING(tier)
#define AXE_DAMAGE_MAX(tier) AXE_DAMAGE_MIN(tier) + AXE_RANGE(tier)

class Axe : public Weapon
{
public:
	virtual std::string getWeaponAttackSound() override;
	virtual std::string getWeaponImpactSound() override;
	
protected:
	Axe(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Axe();

private:
	typedef Weapon super;
};
