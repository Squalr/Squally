#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class WoodenMallet : public Mace
{
public:
	static WoodenMallet* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWoodenMallet;

protected:
	WoodenMallet();
	virtual ~WoodenMallet();

private:
	typedef Mace super;
};
