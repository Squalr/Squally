#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class BoneBow : public Bow
{
public:
	static BoneBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyBoneBow;

protected:
	BoneBow();
	virtual ~BoneBow();

private:
	typedef Bow super;
};
