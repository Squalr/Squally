#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class MarineNecklace : public Necklace
{
public:
	static MarineNecklace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MarineNecklace();
	virtual ~MarineNecklace();

private:
	typedef Necklace super;
};
