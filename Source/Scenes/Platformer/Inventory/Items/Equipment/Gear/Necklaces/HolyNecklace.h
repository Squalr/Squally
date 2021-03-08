#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class HolyNecklace : public Necklace
{
public:
	static HolyNecklace* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	HolyNecklace();
	virtual ~HolyNecklace();

private:
	typedef Necklace super;
};
