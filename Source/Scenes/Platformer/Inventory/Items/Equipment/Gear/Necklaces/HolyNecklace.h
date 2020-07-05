#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class HolyNecklace : public Necklace
{
public:
	static HolyNecklace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	HolyNecklace();
	virtual ~HolyNecklace();

private:
	typedef Necklace super;
};
