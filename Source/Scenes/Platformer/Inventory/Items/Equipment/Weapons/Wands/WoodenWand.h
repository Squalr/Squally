#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class WoodenWand : public Wand
{
public:
	static WoodenWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWoodenWand;

protected:
	WoodenWand();
	virtual ~WoodenWand();

private:
	typedef Wand super;
};
