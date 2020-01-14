#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class EnchantedWand : public Weapon
{
public:
	static EnchantedWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyEnchantedWand;

protected:
	EnchantedWand();
	virtual ~EnchantedWand();

private:
	typedef Weapon super;
};
