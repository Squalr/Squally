#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class CopperSword : public Sword
{
public:
	static CopperSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCopperSword;

protected:
	CopperSword();
	virtual ~CopperSword();

private:
	typedef Sword super;
};
