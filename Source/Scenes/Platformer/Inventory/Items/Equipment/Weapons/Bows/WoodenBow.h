#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class WoodenBow : public Bow
{
public:
	static WoodenBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWoodenBow;

protected:
	WoodenBow();
	virtual ~WoodenBow();

private:
	typedef Bow super;
};
