#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class Cleaver : public Sword
{
public:
	static Cleaver* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCleaver;

protected:
	Cleaver();
	virtual ~Cleaver();

private:
	typedef Sword super;
};
