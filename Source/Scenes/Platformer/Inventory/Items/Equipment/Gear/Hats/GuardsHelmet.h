#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class GuardsHelmet : public Hat
{
public:
	static GuardsHelmet* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyGuardsHelmet;

protected:
	GuardsHelmet();
	virtual ~GuardsHelmet();

private:
	typedef Hat super;
};
