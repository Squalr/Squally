#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WarlocksHeaddress : public Hat
{
public:
	static WarlocksHeaddress* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWarlocksHeaddress;

protected:
	WarlocksHeaddress();
	virtual ~WarlocksHeaddress();

private:
	typedef Hat super;
};
