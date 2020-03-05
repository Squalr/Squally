#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class GlowingPendant : public Necklace
{
public:
	static GlowingPendant* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyGlowingPendant;

protected:
	GlowingPendant();
	virtual ~GlowingPendant();

private:
	typedef Necklace super;
};
