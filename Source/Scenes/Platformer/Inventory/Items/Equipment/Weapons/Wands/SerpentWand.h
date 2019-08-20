#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class SerpentWand : public Weapon
{
public:
	static SerpentWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySerpentWand;

protected:
	SerpentWand();
	~SerpentWand();

private:
	typedef Weapon super;
};
