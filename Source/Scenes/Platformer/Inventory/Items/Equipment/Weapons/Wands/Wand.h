#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

// Wands: Ranged out of combat, Medium damage variance, very low base damage, high mana, fast timeline speed
#define WAND_RANGE(tier) (int)std::ceil((float)tier / 2.0f) + 1
#define WAND_DAMAGE_MIN(tier) BASE_SCALING(tier) - (int)std::ceil((float)tier / 1.5f) - (tier <= 1 ? 1 : 0)
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
