#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class EmeraldWand : public Wand
{
public:
	static EmeraldWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyEmeraldWand;

protected:
	EmeraldWand();
	virtual ~EmeraldWand();

private:
	typedef Wand super;
};
