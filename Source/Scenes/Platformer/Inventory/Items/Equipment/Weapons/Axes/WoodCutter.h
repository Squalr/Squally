#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class WoodCutter : public Weapon
{
public:
	static WoodCutter* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Size getWeaponCollisionSize() override;
	cocos2d::Vec2 getWeaponOffset() override;

	static const std::string SaveKeyWoodCutter;

protected:
	WoodCutter();
	virtual ~WoodCutter();

private:
	typedef Weapon super;
};
