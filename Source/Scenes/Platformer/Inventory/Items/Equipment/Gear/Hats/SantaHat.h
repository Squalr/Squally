#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class SantaHat : public Hat
{
public:
	static SantaHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySantaHat;

protected:
	SantaHat();
	virtual ~SantaHat();

private:
	typedef Hat super;
};
