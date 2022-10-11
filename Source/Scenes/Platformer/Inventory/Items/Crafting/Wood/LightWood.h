#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class LightWood : public Crafting
{
public:
	static LightWood* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	LightWood();
	virtual ~LightWood();

private:
	typedef Crafting super;
};
