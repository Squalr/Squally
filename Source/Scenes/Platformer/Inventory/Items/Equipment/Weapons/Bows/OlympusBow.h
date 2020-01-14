#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class OlympusBow : public Weapon
{
public:
	static OlympusBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyOlympusBow;

protected:
	OlympusBow();
	virtual ~OlympusBow();

private:
	typedef Weapon super;
};
