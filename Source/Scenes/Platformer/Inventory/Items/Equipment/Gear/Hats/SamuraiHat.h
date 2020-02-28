#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class SamuraiHat : public Hat
{
public:
	static SamuraiHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySamuraiHat;

protected:
	SamuraiHat();
	virtual ~SamuraiHat();

private:
	typedef Hat super;
};
