#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class DarkHeartBand : public Ring
{
public:
	static DarkHeartBand* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	DarkHeartBand();
	virtual ~DarkHeartBand();

private:
	typedef Ring super;
};
