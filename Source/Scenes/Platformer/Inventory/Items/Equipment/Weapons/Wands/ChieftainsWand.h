#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class ChieftainsWand : public Weapon
{
public:
	static ChieftainsWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyChieftainsWand;

protected:
	ChieftainsWand();
	virtual ~ChieftainsWand();

private:
	typedef Weapon super;
};
