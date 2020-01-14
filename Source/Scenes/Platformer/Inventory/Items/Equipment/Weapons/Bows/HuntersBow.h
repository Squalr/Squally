#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class HuntersBow : public Weapon
{
public:
	static HuntersBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyHuntersBow;

protected:
	HuntersBow();
	virtual ~HuntersBow();

private:
	typedef Weapon super;
};
