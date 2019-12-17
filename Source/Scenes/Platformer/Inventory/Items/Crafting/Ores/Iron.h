#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Iron : public Crafting
{
public:
	static Iron* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyIron;

protected:
	Iron();
	virtual ~Iron();

private:
	typedef Crafting super;
};
