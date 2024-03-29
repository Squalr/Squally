#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class WoodenSword : public Sword
{
public:
	static WoodenSword* create();

	std::string getWeaponImpactSound() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	WoodenSword();
	virtual ~WoodenSword();

private:
	typedef Sword super;
};
