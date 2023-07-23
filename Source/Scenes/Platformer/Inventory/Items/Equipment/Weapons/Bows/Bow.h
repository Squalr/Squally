#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

// Bows: Ranged out of combat, medium damage variance, lower base damage, medium mana, very fast timeline speed
#define BOW_RANGE(tier) (int)std::ceil((float)tier * 2.25f / 4.0f) + 2 - (tier <= 2 ? tier : 0)
#define BOW_DAMAGE_MIN(tier) BASE_SCALING(tier) - (int)std::ceil((float)tier / 2.0f) - (tier <= 2 ? 1 : 0)
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
