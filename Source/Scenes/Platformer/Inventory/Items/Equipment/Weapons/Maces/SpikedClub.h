#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class SpikedClub : public Weapon
{
public:
	static SpikedClub* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySpikedClub;

protected:
	SpikedClub();
	virtual ~SpikedClub();

private:
	typedef Weapon super;
};
