#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class BrocksHelm : public Hat
{
public:
	static BrocksHelm* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	BrocksHelm();
	virtual ~BrocksHelm();

private:
	typedef Hat super;
};
