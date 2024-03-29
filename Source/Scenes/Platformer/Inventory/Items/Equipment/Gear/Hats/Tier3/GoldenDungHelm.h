#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class GoldenDungHelm : public Hat
{
public:
	static GoldenDungHelm* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	GoldenDungHelm();
	virtual ~GoldenDungHelm();

private:
	typedef Hat super;
};
