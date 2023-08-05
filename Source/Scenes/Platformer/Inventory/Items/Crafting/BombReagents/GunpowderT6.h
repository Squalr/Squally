#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GunpowderT6 : public Crafting
{
public:
	static GunpowderT6* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GunpowderT6();
	virtual ~GunpowderT6();

private:
	typedef Crafting super;
};
