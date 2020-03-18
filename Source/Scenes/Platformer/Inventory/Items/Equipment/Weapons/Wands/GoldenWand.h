#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class GoldenWand : public Wand
{
public:
	static GoldenWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyGoldenWand;

protected:
	GoldenWand();
	virtual ~GoldenWand();

private:
	typedef Wand super;
};
