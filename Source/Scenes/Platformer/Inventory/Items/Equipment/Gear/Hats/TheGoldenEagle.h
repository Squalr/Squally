#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class TheGoldenEagle : public Hat
{
public:
	static TheGoldenEagle* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyTheGoldenEagle;

protected:
	TheGoldenEagle();
	virtual ~TheGoldenEagle();

private:
	typedef Hat super;
};
