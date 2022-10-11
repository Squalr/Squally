#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class MarineNecklace : public Necklace
{
public:
	static MarineNecklace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	MarineNecklace();
	virtual ~MarineNecklace();

private:
	typedef Necklace super;
};
