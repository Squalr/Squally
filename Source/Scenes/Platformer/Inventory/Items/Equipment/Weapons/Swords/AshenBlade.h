#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class AshenBlade : public Weapon
{
public:
	static AshenBlade* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyAshenBlade;

protected:
	AshenBlade();
	virtual ~AshenBlade();

private:
	typedef Weapon super;
};
