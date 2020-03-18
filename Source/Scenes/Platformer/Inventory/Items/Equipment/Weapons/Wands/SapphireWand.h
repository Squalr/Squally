#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class SapphireWand : public Wand
{
public:
	static SapphireWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeySapphireWand;

protected:
	SapphireWand();
	virtual ~SapphireWand();

private:
	typedef Wand super;
};
