#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

#define BOW_RANGE(tier) (int)std::ceil((float)tier * 3.0f / 4.0f) + 2 // Bows: Medium damage variance, lower base damage, very fast timeline speed
#define BOW_DAMAGE_MIN(tier) BASE_SCALING(tier) - (int)std::ceil(tier * 3 / 4)
#define BOW_DAMAGE_MAX(tier) BOW_DAMAGE_MIN(tier) + BOW_RANGE(tier)

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
