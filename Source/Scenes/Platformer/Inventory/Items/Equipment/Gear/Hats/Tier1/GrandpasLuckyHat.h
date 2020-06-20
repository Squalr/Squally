#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class GrandpasLuckyHat : public Hat
{
public:
	static GrandpasLuckyHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKey;

protected:
	GrandpasLuckyHat();
	virtual ~GrandpasLuckyHat();

private:
	typedef Hat super;
};
