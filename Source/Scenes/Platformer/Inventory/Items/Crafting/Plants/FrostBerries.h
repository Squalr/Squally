#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class FrostBerries : public Crafting
{
public:
	static FrostBerries* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	FrostBerries();
	virtual ~FrostBerries();

private:
	typedef Crafting super;
};
