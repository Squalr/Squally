#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class ArcaneWand : public Weapon
{
public:
	static ArcaneWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyArcaneWand;

protected:
	ArcaneWand();
	virtual ~ArcaneWand();

private:
	typedef Weapon super;
};
