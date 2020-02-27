#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class BlueSword : public Sword
{
public:
	static BlueSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBlueSword;

protected:
	BlueSword();
	virtual ~BlueSword();

private:
	typedef Sword super;
};
