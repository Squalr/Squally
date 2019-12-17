#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Stone : public Crafting
{
public:
	static Stone* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyStone;

protected:
	Stone();
	virtual ~Stone();

private:
	typedef Crafting super;
};
