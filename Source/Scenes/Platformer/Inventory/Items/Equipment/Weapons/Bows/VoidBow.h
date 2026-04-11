#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class VoidBow : public Bow
{
public:
	static VoidBow* create();

	cocos2d::Vec2 getDisplayOffset() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	VoidBow();
	virtual ~VoidBow();

private:
	typedef Bow super;
};
