#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class WoodenClub : public Mace
{
public:
	static WoodenClub* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	WoodenClub();
	virtual ~WoodenClub();

private:
	typedef Mace super;
};
