#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class DemonRoot : public Crafting
{
public:
	static DemonRoot* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	DemonRoot();
	virtual ~DemonRoot();

private:
	typedef Crafting super;
};
