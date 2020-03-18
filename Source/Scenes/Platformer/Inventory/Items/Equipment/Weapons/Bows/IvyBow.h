#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class IvyBow : public Bow
{
public:
	static IvyBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyIvyBow;

protected:
	IvyBow();
	virtual ~IvyBow();

private:
	typedef Bow super;
};
