#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class SkullBand : public Ring
{
public:
	static SkullBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	SkullBand();
	virtual ~SkullBand();

private:
	typedef Ring super;
};
