#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class AquaMarineNecklace : public Necklace
{
public:
	static AquaMarineNecklace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	AquaMarineNecklace();
	virtual ~AquaMarineNecklace();

private:
	typedef Necklace super;
};
