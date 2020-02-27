#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Spears/Spear.h"

class Impaler : public Spear
{
public:
	static Impaler* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyImpaler;

protected:
	Impaler();
	virtual ~Impaler();

private:
	typedef Spear super;
};
