#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class HeartBand : public Ring
{
public:
	static HeartBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	HeartBand();
	virtual ~HeartBand();

private:
	typedef Ring super;
};
