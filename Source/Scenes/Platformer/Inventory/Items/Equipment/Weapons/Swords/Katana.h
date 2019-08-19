#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Katana : public Weapon
{
public:
	static Katana* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyKatana;

protected:
	Katana();
	~Katana();

private:
	typedef Weapon super;
};
