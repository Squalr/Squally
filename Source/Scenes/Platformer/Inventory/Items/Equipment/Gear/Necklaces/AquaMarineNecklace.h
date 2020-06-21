#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class AquaMarineNecklace : public Necklace
{
public:
	static AquaMarineNecklace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	AquaMarineNecklace();
	virtual ~AquaMarineNecklace();

private:
	typedef Necklace super;
};
