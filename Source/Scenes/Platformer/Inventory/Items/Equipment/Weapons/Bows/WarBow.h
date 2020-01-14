#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class WarBow : public Weapon
{
public:
	static WarBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWarBow;

protected:
	WarBow();
	virtual ~WarBow();

private:
	typedef Weapon super;
};
