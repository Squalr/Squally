#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class IronSword : public Weapon
{
public:
	static IronSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyIronSword;

protected:
	IronSword();
	~IronSword();

private:
	typedef Weapon super;
};
