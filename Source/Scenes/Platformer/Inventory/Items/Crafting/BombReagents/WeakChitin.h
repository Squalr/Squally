#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class WeakChitin : public Crafting
{
public:
	static WeakChitin* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	WeakChitin();
	virtual ~WeakChitin();

private:
	typedef Crafting super;
};
