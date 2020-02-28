#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WizardsHatWater : public Hat
{
public:
	static WizardsHatWater* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWizardsHatWater;

protected:
	WizardsHatWater();
	virtual ~WizardsHatWater();

private:
	typedef Hat super;
};
