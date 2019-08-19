#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Rapier : public Weapon
{
public:
	static Rapier* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyRapier;

protected:
	Rapier();
	~Rapier();

private:
	typedef Weapon super;
};
