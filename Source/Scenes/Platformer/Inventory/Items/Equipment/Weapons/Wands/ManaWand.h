#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class ManaWand : public Wand
{
public:
	static ManaWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyManaWand;

protected:
	ManaWand();
	virtual ~ManaWand();

private:
	typedef Wand super;
};
