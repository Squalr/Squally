#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WitchesHat : public Hat
{
public:
	static WitchesHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWitchesHat;

protected:
	WitchesHat();
	virtual ~WitchesHat();

private:
	typedef Hat super;
};
