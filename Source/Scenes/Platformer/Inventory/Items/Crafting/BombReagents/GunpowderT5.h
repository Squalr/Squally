#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GunpowderT5 : public Crafting
{
public:
	static GunpowderT5* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GunpowderT5();
	virtual ~GunpowderT5();

private:
	typedef Crafting super;
};
