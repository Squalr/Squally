#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class GunpowderT3 : public Crafting
{
public:
	static GunpowderT3* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GunpowderT3();
	virtual ~GunpowderT3();

private:
	typedef Crafting super;
};
