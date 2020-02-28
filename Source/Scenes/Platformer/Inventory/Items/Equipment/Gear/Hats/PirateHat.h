#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class PirateHat : public Hat
{
public:
	static PirateHat* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyPirateHat;

protected:
	PirateHat();
	virtual ~PirateHat();

private:
	typedef Hat super;
};
