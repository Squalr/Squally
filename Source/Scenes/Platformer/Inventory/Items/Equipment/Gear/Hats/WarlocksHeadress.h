#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WarlocksHeadress : public Hat
{
public:
	static WarlocksHeadress* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWarlocksHeadress;

protected:
	WarlocksHeadress();
	virtual ~WarlocksHeadress();

private:
	typedef Hat super;
};
