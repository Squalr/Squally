#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class IronSword : public Sword
{
public:
	static IronSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyIronSword;

protected:
	IronSword();
	virtual ~IronSword();

private:
	typedef Sword super;
};
