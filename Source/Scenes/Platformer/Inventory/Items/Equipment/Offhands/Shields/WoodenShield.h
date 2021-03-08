#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"

class WoodenShield : public Offhand
{
public:
	static WoodenShield* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	WoodenShield();
	virtual ~WoodenShield();

private:
	typedef Offhand super;
};
