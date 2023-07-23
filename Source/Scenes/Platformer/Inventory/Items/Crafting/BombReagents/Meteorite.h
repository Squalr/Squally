#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Meteorite : public Crafting
{
public:
	static Meteorite* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	Meteorite();
	virtual ~Meteorite();

private:
	typedef Crafting super;
};
