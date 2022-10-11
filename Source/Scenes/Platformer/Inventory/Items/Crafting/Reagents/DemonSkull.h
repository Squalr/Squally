#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class DemonSkull : public Crafting
{
public:
	static DemonSkull* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	DemonSkull();
	virtual ~DemonSkull();

private:
	typedef Crafting super;
};
