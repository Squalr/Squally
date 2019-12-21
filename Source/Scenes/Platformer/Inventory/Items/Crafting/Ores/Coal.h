#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Coal : public Crafting
{
public:
	static Coal* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCoal;

protected:
	Coal();
	virtual ~Coal();

private:
	typedef Crafting super;
};
