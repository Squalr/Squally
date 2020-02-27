#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/Axe.h"

class Cleaver : public Axe
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
	typedef Axe super;
};
