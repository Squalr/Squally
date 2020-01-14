#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class FangBlade : public Weapon
{
public:
	static FangBlade* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyFangBlade;

protected:
	FangBlade();
	virtual ~FangBlade();

private:
	typedef Weapon super;
};
