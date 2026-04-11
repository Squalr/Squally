#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class SteelSword : public Sword
{
public:
	static SteelSword* create();

	cocos2d::Vec2 getWeaponCollisionOffset() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	SteelSword();
	virtual ~SteelSword();

private:
	typedef Sword super;
};
