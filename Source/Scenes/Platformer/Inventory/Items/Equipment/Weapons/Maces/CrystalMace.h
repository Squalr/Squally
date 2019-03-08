#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CrystalMace : public Weapon
{
public:
	static CrystalMace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCrystalMace;

protected:
	CrystalMace();
	virtual ~CrystalMace();

private:
	typedef Weapon super;
};
