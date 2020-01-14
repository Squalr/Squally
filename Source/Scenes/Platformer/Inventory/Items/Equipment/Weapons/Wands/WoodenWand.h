#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class WoodenWand : public Weapon
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
	typedef Weapon super;
};
