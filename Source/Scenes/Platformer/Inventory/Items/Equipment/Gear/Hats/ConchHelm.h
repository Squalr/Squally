#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class ConchHelm : public Hat
{
public:
	static ConchHelm* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyConchHelm;

protected:
	ConchHelm();
	virtual ~ConchHelm();

private:
	typedef Hat super;
};
