#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"

class WoodenShield : public Offhand
{
public:
	static WoodenShield* create();

	Item* clone() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyWoodenShield;

protected:
	WoodenShield();
	virtual ~WoodenShield();

private:
	typedef Offhand super;
};
