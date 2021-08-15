#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

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

protected:
	Weapon(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats);
	virtual ~Weapon();

private:
	typedef Equipable super;

	int minAttack = 0;
	int maxAttack = 0;
};
