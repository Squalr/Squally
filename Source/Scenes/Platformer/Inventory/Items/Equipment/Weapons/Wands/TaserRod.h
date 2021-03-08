#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class TaserRod : public Wand
{
public:
	static TaserRod* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	TaserRod();
	virtual ~TaserRod();

private:
	typedef Wand super;
};
