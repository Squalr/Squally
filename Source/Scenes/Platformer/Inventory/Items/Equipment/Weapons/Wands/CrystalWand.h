#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class CrystalWand : public Wand
{
public:
	static CrystalWand* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	CrystalWand();
	virtual ~CrystalWand();

private:
	typedef Wand super;
};
