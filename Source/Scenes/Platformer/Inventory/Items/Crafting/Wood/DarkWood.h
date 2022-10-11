#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class DarkWood : public Crafting
{
public:
	static DarkWood* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	DarkWood();
	virtual ~DarkWood();

private:
	typedef Crafting super;
};
