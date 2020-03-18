#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class Dreadmourn : public Sword
{
public:
	static Dreadmourn* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDreadmourn;

protected:
	Dreadmourn();
	virtual ~Dreadmourn();

private:
	typedef Sword super;
};
