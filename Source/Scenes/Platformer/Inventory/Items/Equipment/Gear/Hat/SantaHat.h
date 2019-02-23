#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class SantaHat : public Gear
{
public:
	static SantaHat* create();

	Item* clone() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySantaHat;

protected:
	SantaHat();
	virtual ~SantaHat();

private:
	typedef Gear super;
};
