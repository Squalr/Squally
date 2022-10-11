#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class VoidBow : public Bow
{
public:
	static VoidBow* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	VoidBow();
	virtual ~VoidBow();

private:
	typedef Bow super;
};
