#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class WoodenRapier : public Sword
{
public:
	static WoodenRapier* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyWoodenRapier;

protected:
	WoodenRapier();
	virtual ~WoodenRapier();

private:
	typedef Sword super;
};
