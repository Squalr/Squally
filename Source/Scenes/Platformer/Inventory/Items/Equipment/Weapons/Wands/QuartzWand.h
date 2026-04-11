#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class QuartzWand : public Wand
{
public:
	static QuartzWand* create();

	cocos2d::Vec2 getWeaponCollisionOffset() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	QuartzWand();
	virtual ~QuartzWand();

private:
	typedef Wand super;
};
