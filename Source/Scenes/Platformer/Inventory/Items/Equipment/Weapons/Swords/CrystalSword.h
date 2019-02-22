#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CrystalSword : public Weapon
{
public:
	static CrystalSword* create();

	std::string getSerializationKey() override;

	static const std::string SaveKeyCrystalSword;

protected:
	CrystalSword();
	virtual ~CrystalSword();

private:
	typedef Weapon super;
};
