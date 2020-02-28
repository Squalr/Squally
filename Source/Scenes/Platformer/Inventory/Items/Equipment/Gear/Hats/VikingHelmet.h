#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class VikingHelmet : public Hat
{
public:
	static VikingHelmet* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyVikingHelmet;

protected:
	VikingHelmet();
	virtual ~VikingHelmet();

private:
	typedef Hat super;
};
