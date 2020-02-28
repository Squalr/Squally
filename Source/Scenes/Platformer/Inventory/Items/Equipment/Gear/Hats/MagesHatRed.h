#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class MagesHatRed : public Hat
{
public:
	static MagesHatRed* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyMagesHatRed;

protected:
	MagesHatRed();
	virtual ~MagesHatRed();

private:
	typedef Hat super;
};
