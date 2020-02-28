#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class WizardsHatArcane : public Hat
{
public:
	static WizardsHatArcane* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyWizardsHatArcane;

protected:
	WizardsHatArcane();
	virtual ~WizardsHatArcane();

private:
	typedef Hat super;
};
