#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class AmethystNecklace : public Necklace
{
public:
	static AmethystNecklace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	AmethystNecklace();
	virtual ~AmethystNecklace();

private:
	typedef Necklace super;
};
