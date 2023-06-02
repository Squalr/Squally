#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class GoldenRing : public Ring
{
public:
	static GoldenRing* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	GoldenRing();
	virtual ~GoldenRing();

private:
	typedef Ring super;
};
