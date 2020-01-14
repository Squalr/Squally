#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class NecroWand : public Weapon
{
public:
	static NecroWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyNecroWand;

protected:
	NecroWand();
	virtual ~NecroWand();

private:
	typedef Weapon super;
};
