#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class GarnetBand : public Ring
{
public:
	static GarnetBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	GarnetBand();
	virtual ~GarnetBand();

private:
	typedef Ring super;
};
