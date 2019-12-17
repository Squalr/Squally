#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Quartz : public Crafting
{
public:
	static Quartz* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyQuartz;

protected:
	Quartz();
	virtual ~Quartz();

private:
	typedef Crafting super;
};
