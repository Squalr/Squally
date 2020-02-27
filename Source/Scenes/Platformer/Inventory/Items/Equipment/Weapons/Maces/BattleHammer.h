#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class BattleHammer : public Mace
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
	virtual ~BattleHammer();

private:
	typedef Mace super;
};
