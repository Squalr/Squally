#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class GardenersHat : public Hat
{
public:
	static GardenersHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyGardenersHat;

protected:
	GardenersHat();
	virtual ~GardenersHat();

private:
	typedef Hat super;
};
