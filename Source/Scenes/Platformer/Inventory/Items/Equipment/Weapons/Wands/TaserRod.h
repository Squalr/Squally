#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class TaserRod : public Weapon
{
public:
	static TaserRod* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyTaserRod;

protected:
	TaserRod();
	virtual ~TaserRod();

private:
	typedef Weapon super;
};
