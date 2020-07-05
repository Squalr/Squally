#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class SapphireNecklace : public Necklace
{
public:
	static SapphireNecklace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	SapphireNecklace();
	virtual ~SapphireNecklace();

private:
	typedef Necklace super;
};
