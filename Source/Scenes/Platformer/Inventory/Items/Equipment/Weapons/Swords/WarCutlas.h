#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class WarCutlas : public Sword
{
public:
	static WarCutlas* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyWarCutlas;

protected:
	WarCutlas();
	virtual ~WarCutlas();

private:
	typedef Sword super;
};
