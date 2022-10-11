#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class SapphireBand : public Ring
{
public:
	static SapphireBand* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	SapphireBand();
	virtual ~SapphireBand();

private:
	typedef Ring super;
};
