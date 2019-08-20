#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class SkullCrusher : public Weapon
{
public:
	static SkullCrusher* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySkullCrusher;

protected:
	SkullCrusher();
	~SkullCrusher();

private:
	typedef Weapon super;
};
