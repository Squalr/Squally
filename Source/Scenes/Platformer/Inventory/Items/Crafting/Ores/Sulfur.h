#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Sulfur : public Crafting
{
public:
	static Sulfur* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySulfur;

protected:
	Sulfur();
	virtual ~Sulfur();

private:
	typedef Crafting super;
};
