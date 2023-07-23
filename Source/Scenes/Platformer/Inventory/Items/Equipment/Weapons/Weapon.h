#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

// ceil(sqrt(tier) * (tier + 1)) => 4, 6, 9, 13, 17, 21, 25, 29, 37
#define BASE_SCALING(tier) (int)std::ceil(std::sqrt((float)tier + 1.0f) * ((float)tier + 2.0f)) - 1

class Weapon : public Equipable
{
public:
	int getMinAttack();
	int getMaxAttack();
	virtual float getAttackOnset();
	virtual float getAttackSustain();
	virtual cocos2d::CSize getWeaponCollisionSize();
	virtual cocos2d::Vec2 getWeaponCollisionOffset();
	virtual std::string getWeaponAttackSound();
	virtual std::string getWeaponImpactSound();

protected:
	Weapon(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Weapon();

private:
	typedef Equipable super;

	int minAttack = 0;
	int maxAttack = 0;
};
