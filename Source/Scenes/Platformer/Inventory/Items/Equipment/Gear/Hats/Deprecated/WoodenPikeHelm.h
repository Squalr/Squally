#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WoodenPikeHelm : public Hat
{
public:
	static WoodenPikeHelm* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	WoodenPikeHelm();
	virtual ~WoodenPikeHelm();

private:
	typedef Hat super;
};
