#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class OrnateHat : public Hat
{
public:
	static OrnateHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyOrnateHat;

protected:
	OrnateHat();
	virtual ~OrnateHat();

private:
	typedef Hat super;
};
