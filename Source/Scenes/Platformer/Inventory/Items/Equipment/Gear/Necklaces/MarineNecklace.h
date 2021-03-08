#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class MarineNecklace : public Necklace
{
public:
	static MarineNecklace* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MarineNecklace();
	virtual ~MarineNecklace();

private:
	typedef Necklace super;
};
