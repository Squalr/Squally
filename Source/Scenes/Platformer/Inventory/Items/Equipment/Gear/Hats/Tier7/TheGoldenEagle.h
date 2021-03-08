#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class TheGoldenEagle : public Hat
{
public:
	static TheGoldenEagle* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKey;

protected:
	TheGoldenEagle();
	virtual ~TheGoldenEagle();

private:
	typedef Hat super;
};
