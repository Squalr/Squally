#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

// Swords: Medium damage variance, medium timeline speed,  balanced hp/mp (favoring hp)
#define SWORD_RANGE(tier) (int)std::ceil((float)tier * 3.0f / 4.0f) + 1
#define SWORD_DAMAGE_MIN(tier) BASE_SCALING(tier) - (tier <= 2 ? tier : 0)
#define SWORD_DAMAGE_MAX(tier) SWORD_DAMAGE_MIN(tier) + SWORD_RANGE(tier)

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
