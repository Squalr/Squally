#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class VoidFlower : public Crafting
{
public:
	static VoidFlower* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	VoidFlower();
	virtual ~VoidFlower();

private:
	typedef Crafting super;
};
