#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class LeatherCap : public Hat
{
public:
	static LeatherCap* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyLeatherCap;

protected:
	LeatherCap();
	virtual ~LeatherCap();

private:
	typedef Hat super;
};
