#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class Gladius : public Sword
{
public:
	static Gladius* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyGladius;

protected:
	Gladius();
	virtual ~Gladius();

private:
	typedef Sword super;
};
