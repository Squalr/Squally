#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"

class WoodenShield : public Offhand
{
public:
	static WoodenShield* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	WoodenShield();
	virtual ~WoodenShield();

private:
	typedef Offhand super;
};
