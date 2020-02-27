#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class CrystalSword : public Sword
{
public:
	static CrystalSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCrystalSword;

protected:
	CrystalSword();
	virtual ~CrystalSword();

private:
	typedef Sword super;
};
