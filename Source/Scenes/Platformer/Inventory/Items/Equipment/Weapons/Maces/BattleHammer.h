#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class BattleHammer : public Weapon
{
public:
	static BattleHammer* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyBattleHammer;

protected:
	BattleHammer();
	~BattleHammer();

private:
	typedef Weapon super;
};
