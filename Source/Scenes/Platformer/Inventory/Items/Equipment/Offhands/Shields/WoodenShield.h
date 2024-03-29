#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"

class WoodenShield : public Offhand
{
public:
	static WoodenShield* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	WoodenShield();
	virtual ~WoodenShield();

private:
	typedef Offhand super;
};
