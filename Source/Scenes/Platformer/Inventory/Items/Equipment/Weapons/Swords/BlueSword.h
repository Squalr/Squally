#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class BlueSword : public Weapon
{
public:
	static BlueSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBlueSword;

protected:
	BlueSword();
	~BlueSword();

private:
	typedef Weapon super;
};
