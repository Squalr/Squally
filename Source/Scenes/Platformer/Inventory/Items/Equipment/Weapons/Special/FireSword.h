#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class FireSword : public Sword
{
public:
	static FireSword* create();

	cocos2d::Vec2 getWeaponCollisionOffset() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	FireSword();
	virtual ~FireSword();

private:
	typedef Sword super;
};
