#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

#define MACE_RANGE(tier) tier / 2 + 1 // Maces: Low damage variance, very slow timeline speed
#define MACE_DAMAGE_MIN(tier) BASE_SCALING(tier)
#define MACE_DAMAGE_MAX(tier) MACE_DAMAGE_MIN(tier) + MACE_RANGE(tier)

class Mace : public Weapon
{
public:
	virtual std::string getWeaponAttackSound() override;
	virtual std::string getWeaponImpactSound() override;
	
protected:
	Mace(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Mace();

private:
	typedef Weapon super;
};
