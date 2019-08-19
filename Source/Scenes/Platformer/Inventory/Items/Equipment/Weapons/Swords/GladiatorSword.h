#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class GladiatorSword : public Weapon
{
public:
	static GladiatorSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyGladiatorSword;

protected:
	GladiatorSword();
	~GladiatorSword();

private:
	typedef Weapon super;
};
