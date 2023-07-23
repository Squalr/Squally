#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class BronzeRing : public Ring
{
public:
	static BronzeRing* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	BronzeRing();
	virtual ~BronzeRing();

private:
	typedef Ring super;
};
