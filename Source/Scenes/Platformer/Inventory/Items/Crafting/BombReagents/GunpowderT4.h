#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GunpowderT4 : public Crafting
{
public:
	static GunpowderT4* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GunpowderT4();
	virtual ~GunpowderT4();

private:
	typedef Crafting super;
};
