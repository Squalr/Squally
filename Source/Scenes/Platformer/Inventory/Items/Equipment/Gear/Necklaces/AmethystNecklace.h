#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class AmethystNecklace : public Necklace
{
public:
	static AmethystNecklace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	AmethystNecklace();
	virtual ~AmethystNecklace();

private:
	typedef Necklace super;
};
