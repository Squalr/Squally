#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Rune : public Crafting
{
public:
	static Rune* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyRune;

protected:
	Rune();
	virtual ~Rune();

private:
	typedef Crafting super;
};
