#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class CompositeBow : public Bow
{
public:
	static CompositeBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCompositeBow;

protected:
	CompositeBow();
	virtual ~CompositeBow();

private:
	typedef Bow super;
};
