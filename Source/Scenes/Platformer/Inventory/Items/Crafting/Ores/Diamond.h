#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Diamond : public Crafting
{
public:
	static Diamond* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDiamond;

protected:
	Diamond();
	virtual ~Diamond();

private:
	typedef Crafting super;
};
