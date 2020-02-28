#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WizardsHatEarth : public Hat
{
public:
	static WizardsHatEarth* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWizardsHatEarth;

protected:
	WizardsHatEarth();
	virtual ~WizardsHatEarth();

private:
	typedef Hat super;
};
