#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class BoneHammer : public Weapon
{
public:
	static BoneHammer* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyBoneHammer;

protected:
	BoneHammer();
	~BoneHammer();

private:
	typedef Weapon super;
};
