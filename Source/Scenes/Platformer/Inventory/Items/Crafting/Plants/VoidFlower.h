#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class VoidFlower : public Crafting
{
public:
	static VoidFlower* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	VoidFlower();
	virtual ~VoidFlower();

private:
	typedef Crafting super;
};
