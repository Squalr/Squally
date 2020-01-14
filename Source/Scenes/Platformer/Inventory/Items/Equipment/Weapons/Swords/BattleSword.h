#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class BattleSword : public Weapon
{
public:
	static BattleSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBattleSword;

protected:
	BattleSword();
	virtual ~BattleSword();

private:
	typedef Weapon super;
};
