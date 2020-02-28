#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WoodenPikeHelm : public Hat
{
public:
	static WoodenPikeHelm* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWoodenPikeHelm;

protected:
	WoodenPikeHelm();
	virtual ~WoodenPikeHelm();

private:
	typedef Hat super;
};
