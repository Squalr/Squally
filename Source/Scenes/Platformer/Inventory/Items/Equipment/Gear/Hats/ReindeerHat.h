#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class ReindeerHat : public Hat
{
public:
	static ReindeerHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyReindeerHat;

protected:
	ReindeerHat();
	virtual ~ReindeerHat();

private:
	typedef Hat super;
};
