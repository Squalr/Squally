#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class BoneBow : public Weapon
{
public:
	static BoneBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyBoneBow;

protected:
	BoneBow();
	~BoneBow();

private:
	typedef Weapon super;
};
