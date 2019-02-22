#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

class SantaHat : public Gear
{
public:
	static SantaHat* create();

	std::string getSerializationKey() override;

	static const std::string SaveKeySantaHat;

protected:
	SantaHat();
	virtual ~SantaHat();

private:
	typedef Gear super;
};
