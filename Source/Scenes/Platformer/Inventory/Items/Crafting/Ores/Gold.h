#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Gold : public Crafting
{
public:
	static Gold* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyGold;

protected:
	Gold();
	virtual ~Gold();

private:
	typedef Crafting super;
};
