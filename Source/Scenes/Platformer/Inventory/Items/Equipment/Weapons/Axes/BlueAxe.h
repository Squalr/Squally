#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class BlueAxe : public Weapon
{
public:
	static BlueAxe* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBlueAxe;

protected:
	BlueAxe();
	virtual ~BlueAxe();

private:
	typedef Weapon super;
};
