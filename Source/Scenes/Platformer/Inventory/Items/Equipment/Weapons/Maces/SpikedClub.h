#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class SpikedClub : public Mace
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
	typedef Mace super;
};
