#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class TopazPendant : public Necklace
{
public:
	static TopazPendant* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	TopazPendant();
	virtual ~TopazPendant();

private:
	typedef Necklace super;
};
