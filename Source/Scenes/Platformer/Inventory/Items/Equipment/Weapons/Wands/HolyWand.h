#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class HolyWand : public Weapon
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
	typedef Weapon super;
};
