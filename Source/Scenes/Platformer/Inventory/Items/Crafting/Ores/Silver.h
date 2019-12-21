#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Silver : public Crafting
{
public:
	static Silver* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySilver;

protected:
	Silver();
	virtual ~Silver();

private:
	typedef Crafting super;
};
