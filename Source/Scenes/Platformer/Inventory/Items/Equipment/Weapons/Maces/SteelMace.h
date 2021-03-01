#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class SteelMace : public Mace
{
public:
	static SteelMace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	SteelMace();
	virtual ~SteelMace();

private:
	typedef Mace super;
};
