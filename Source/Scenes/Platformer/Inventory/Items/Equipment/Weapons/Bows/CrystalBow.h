#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class CrystalBow : public Bow
{
public:
	static CrystalBow* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	CrystalBow();
	virtual ~CrystalBow();

private:
	typedef Bow super;
};
