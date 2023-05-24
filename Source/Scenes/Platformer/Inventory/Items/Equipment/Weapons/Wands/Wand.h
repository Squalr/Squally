#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

#define WAND_RANGE(tier) (int)std::ceil((float)tier * 3.0f / 4.0f) + 2 // Bows: Medium damage variance, lower base damage, fast timeline speed
#define WAND_DAMAGE_MIN(tier) BASE_SCALING(tier) - (int)std::ceil(tier * 3 / 4)
#define WAND_DAMAGE_MAX(tier) WAND_DAMAGE_MIN(tier) + WAND_RANGE(tier)

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
