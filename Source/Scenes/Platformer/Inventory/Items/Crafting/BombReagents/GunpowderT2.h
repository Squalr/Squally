#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GunpowderT2 : public Crafting
{
public:
	static GunpowderT2* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GunpowderT2();
	virtual ~GunpowderT2();

private:
	typedef Crafting super;
};
