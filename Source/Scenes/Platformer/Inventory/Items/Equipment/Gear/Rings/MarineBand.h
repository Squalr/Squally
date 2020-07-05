#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class MarineBand : public Ring
{
public:
	static MarineBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MarineBand();
	virtual ~MarineBand();

private:
	typedef Ring super;
};
