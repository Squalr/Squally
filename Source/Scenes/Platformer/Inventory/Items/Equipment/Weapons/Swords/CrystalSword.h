#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CrystalSword : public Weapon
{
public:
	CrystalSword* create();

protected:
	CrystalSword();
	virtual ~CrystalSword();

private:
	typedef Weapon super;
};
