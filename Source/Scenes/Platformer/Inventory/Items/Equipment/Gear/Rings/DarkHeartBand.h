#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class DarkHeartBand : public Ring
{
public:
	static DarkHeartBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	DarkHeartBand();
	virtual ~DarkHeartBand();

private:
	typedef Ring super;
};
