#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CandySword : public Weapon
{
public:
	static CandySword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCandySword;

protected:
	CandySword();
	~CandySword();

private:
	typedef Weapon super;
};
