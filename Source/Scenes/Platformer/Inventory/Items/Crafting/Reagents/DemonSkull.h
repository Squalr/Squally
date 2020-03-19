#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class DemonSkull : public Crafting
{
public:
	static DemonSkull* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	DemonSkull();
	virtual ~DemonSkull();

private:
	typedef Crafting super;
};
