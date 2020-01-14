#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class SteelSword : public Weapon
{
public:
	static SteelSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySteelSword;

protected:
	SteelSword();
	virtual ~SteelSword();

private:
	typedef Weapon super;
};
