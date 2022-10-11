#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class GrandpasLuckyHat : public Hat
{
public:
	static GrandpasLuckyHat* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	GrandpasLuckyHat();
	virtual ~GrandpasLuckyHat();

private:
	typedef Hat super;
};
