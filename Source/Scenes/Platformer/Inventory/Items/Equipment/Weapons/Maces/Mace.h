#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

// Maces: Low damage variance, high base damage, very slow timeline speed, high hp
#define MACE_RANGE(tier) (int)std::ceil((float)tier * 0.25f) + 1
#define MACE_DAMAGE_MIN(tier) BASE_SCALING(tier) + (int)std::ceil((float)tier * 0.5f) - 1
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
