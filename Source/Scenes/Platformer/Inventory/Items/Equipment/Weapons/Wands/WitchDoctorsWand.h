#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class WitchDoctorsWand : public Weapon
{
public:
	static WitchDoctorsWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWitchDoctorsWand;

protected:
	WitchDoctorsWand();
	virtual ~WitchDoctorsWand();

private:
	typedef Weapon super;
};
