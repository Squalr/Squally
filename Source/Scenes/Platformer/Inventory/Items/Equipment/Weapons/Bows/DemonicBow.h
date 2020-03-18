#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class DemonicBow : public Bow
{
public:
	static DemonicBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyDemonicBow;

protected:
	DemonicBow();
	virtual ~DemonicBow();

private:
	typedef Bow super;
};
