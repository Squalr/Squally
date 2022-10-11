#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class HeartBand : public Ring
{
public:
	static HeartBand* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	HeartBand();
	virtual ~HeartBand();

private:
	typedef Ring super;
};
