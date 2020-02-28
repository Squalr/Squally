#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class MagesHatBlue : public Hat
{
public:
	static MagesHatBlue* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyMagesHatBlue;

protected:
	MagesHatBlue();
	virtual ~MagesHatBlue();

private:
	typedef Hat super;
};
