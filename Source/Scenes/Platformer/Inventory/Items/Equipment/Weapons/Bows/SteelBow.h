#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class SteelBow : public Bow
{
public:
	static SteelBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySteelBow;

protected:
	SteelBow();
	virtual ~SteelBow();

private:
	typedef Bow super;
};
