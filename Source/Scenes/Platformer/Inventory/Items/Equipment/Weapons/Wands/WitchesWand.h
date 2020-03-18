#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class WitchesWand : public Wand
{
public:
	static WitchesWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWitchesWand;

protected:
	WitchesWand();
	virtual ~WitchesWand();

private:
	typedef Wand super;
};
