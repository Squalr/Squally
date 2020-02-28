#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class BarbedHelm : public Hat
{
public:
	static BarbedHelm* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyBarbedHelm;

protected:
	BarbedHelm();
	virtual ~BarbedHelm();

private:
	typedef Hat super;
};
