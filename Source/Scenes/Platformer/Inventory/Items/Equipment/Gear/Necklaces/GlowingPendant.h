#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class GlowingPendant : public Necklace
{
public:
	static GlowingPendant* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	GlowingPendant();
	virtual ~GlowingPendant();

private:
	typedef Necklace super;
};
