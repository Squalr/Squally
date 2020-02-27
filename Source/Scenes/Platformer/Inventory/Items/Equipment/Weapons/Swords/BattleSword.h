#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class BattleSword : public Sword
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
	typedef Sword super;
};
