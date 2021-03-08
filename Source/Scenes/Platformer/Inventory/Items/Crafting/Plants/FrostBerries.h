#pragma once

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

class LocalizedString;

class FrostBerries : public Crafting
{
public:
	static FrostBerries* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	FrostBerries();
	virtual ~FrostBerries();

private:
	typedef Crafting super;
};
