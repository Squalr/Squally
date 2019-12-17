#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Dirt : public Crafting
{
public:
	static Dirt* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDirt;

protected:
	Dirt();
	virtual ~Dirt();

private:
	typedef Crafting super;
};
