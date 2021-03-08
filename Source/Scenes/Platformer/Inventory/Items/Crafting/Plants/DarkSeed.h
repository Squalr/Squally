#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class DarkSeed : public Crafting
{
public:
	static DarkSeed* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	DarkSeed();
	virtual ~DarkSeed();

private:
	typedef Crafting super;
};
