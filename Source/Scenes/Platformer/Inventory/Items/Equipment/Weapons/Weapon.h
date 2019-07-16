#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class Weapon : public Equipable
{
public:
	int getMinAttack();
	int getMaxAttack();
	virtual cocos2d::Vec2 getWeaponSizeMultiplier();
	virtual cocos2d::Vec2 getWeaponOffset();

protected:
	Weapon(int minAttack, int maxAttack);
	virtual ~Weapon();

private:
	typedef Equipable super;

	int minAttack;
	int maxAttack;
};
