#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class HolyNecklace : public Necklace
{
public:
	static HolyNecklace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	HolyNecklace();
	virtual ~HolyNecklace();

private:
	typedef Necklace super;
};
