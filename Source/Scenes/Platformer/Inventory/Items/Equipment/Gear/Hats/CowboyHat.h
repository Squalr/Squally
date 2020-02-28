#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class CowboyHat : public Hat
{
public:
	static CowboyHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCowboyHat;

protected:
	CowboyHat();
	virtual ~CowboyHat();

private:
	typedef Hat super;
};
