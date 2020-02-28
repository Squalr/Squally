#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class ToySoldierHat : public Hat
{
public:
	static ToySoldierHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyToySoldierHat;

protected:
	ToySoldierHat();
	virtual ~ToySoldierHat();

private:
	typedef Hat super;
};
