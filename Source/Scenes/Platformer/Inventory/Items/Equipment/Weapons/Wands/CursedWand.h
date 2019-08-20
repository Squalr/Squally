#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CursedWand : public Weapon
{
public:
	static CursedWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCursedWand;

protected:
	CursedWand();
	~CursedWand();

private:
	typedef Weapon super;
};
