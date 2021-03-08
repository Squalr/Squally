#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class TopazPendant : public Necklace
{
public:
	static TopazPendant* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	TopazPendant();
	virtual ~TopazPendant();

private:
	typedef Necklace super;
};
