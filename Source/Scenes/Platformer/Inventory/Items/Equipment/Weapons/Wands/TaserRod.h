#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class TaserRod : public Wand
{
public:
	static TaserRod* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyTaserRod;

protected:
	TaserRod();
	virtual ~TaserRod();

private:
	typedef Wand super;
};
