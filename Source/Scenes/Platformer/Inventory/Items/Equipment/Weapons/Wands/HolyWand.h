#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class HolyWand : public Wand
{
public:
	static HolyWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyHolyWand;

protected:
	HolyWand();
	virtual ~HolyWand();

private:
	typedef Wand super;
};
