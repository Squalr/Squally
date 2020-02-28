#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class SteelHelm : public Hat
{
public:
	static SteelHelm* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySteelHelm;

protected:
	SteelHelm();
	virtual ~SteelHelm();

private:
	typedef Hat super;
};
