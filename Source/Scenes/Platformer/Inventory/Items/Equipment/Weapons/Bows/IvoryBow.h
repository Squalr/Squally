#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class IvoryBow : public Bow
{
public:
	static IvoryBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyIvoryBow;

protected:
	IvoryBow();
	virtual ~IvoryBow();

private:
	typedef Bow super;
};
