#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class CompositeBow : public Weapon
{
public:
	static CompositeBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCompositeBow;

protected:
	CompositeBow();
	~CompositeBow();

private:
	typedef Weapon super;
};
