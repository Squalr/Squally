#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class TigersBane : public Hat
{
public:
	static TigersBane* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyTigersBane;

protected:
	TigersBane();
	virtual ~TigersBane();

private:
	typedef Hat super;
};
