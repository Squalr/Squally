#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class DemonicWand : public Wand
{
public:
	static DemonicWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyDemonicWand;

protected:
	DemonicWand();
	virtual ~DemonicWand();

private:
	typedef Wand super;
};
