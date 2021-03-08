#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Sapphire : public Crafting
{
public:
	static Sapphire* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	Sapphire();
	virtual ~Sapphire();

private:
	typedef Crafting super;
};
