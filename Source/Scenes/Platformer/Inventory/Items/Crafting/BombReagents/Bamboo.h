#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class Bamboo : public Crafting
{
public:
	static Bamboo* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	Bamboo();
	virtual ~Bamboo();

private:
	typedef Crafting super;
};
