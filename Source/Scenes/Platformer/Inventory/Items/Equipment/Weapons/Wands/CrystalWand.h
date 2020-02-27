#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class CrystalWand : public Wand
{
public:
	static CrystalWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCrystalWand;

protected:
	CrystalWand();
	virtual ~CrystalWand();

private:
	typedef Wand super;
};
