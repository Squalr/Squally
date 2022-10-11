#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class SapphireNecklace : public Necklace
{
public:
	static SapphireNecklace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	SapphireNecklace();
	virtual ~SapphireNecklace();

private:
	typedef Necklace super;
};
