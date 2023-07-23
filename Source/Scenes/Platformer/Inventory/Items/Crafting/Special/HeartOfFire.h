#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class HeartOfFire : public Crafting
{
public:
	static HeartOfFire* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	HeartOfFire();
	virtual ~HeartOfFire();

private:
	typedef Crafting super;
};
