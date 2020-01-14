#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class HedgeTrimmer : public Weapon
{
public:
	static HedgeTrimmer* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Size getWeaponCollisionSize() override;
	cocos2d::Vec2 getWeaponOffset() override;

	static const std::string SaveKeyHedgeTrimmer;

protected:
	HedgeTrimmer();
	virtual ~HedgeTrimmer();

private:
	typedef Weapon super;
};
