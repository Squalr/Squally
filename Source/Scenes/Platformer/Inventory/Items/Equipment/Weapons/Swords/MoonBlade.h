#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class MoonBlade : public Weapon
{
public:
	static MoonBlade* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyMoonBlade;

protected:
	MoonBlade();
	virtual ~MoonBlade();

private:
	typedef Weapon super;
};
