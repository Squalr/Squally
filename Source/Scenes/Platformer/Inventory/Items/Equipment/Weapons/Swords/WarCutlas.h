#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class WarCutlas : public Weapon
{
public:
	static WarCutlas* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyWarCutlas;

protected:
	WarCutlas();
	virtual ~WarCutlas();

private:
	typedef Weapon super;
};
