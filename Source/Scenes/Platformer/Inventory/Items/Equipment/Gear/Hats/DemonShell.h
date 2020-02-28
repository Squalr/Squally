#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class DemonShell : public Hat
{
public:
	static DemonShell* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyDemonShell;

protected:
	DemonShell();
	virtual ~DemonShell();

private:
	typedef Hat super;
};
