#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Gladius : public Weapon
{
public:
	static Gladius* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyGladius;

protected:
	Gladius();
	~Gladius();

private:
	typedef Weapon super;
};
