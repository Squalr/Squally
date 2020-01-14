#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CrystalWand : public Weapon
{
public:
	static CrystalWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCrystalWand;

protected:
	CrystalWand();
	virtual ~CrystalWand();

private:
	typedef Weapon super;
};
