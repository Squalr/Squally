#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class BoneHammer : public Mace
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
	virtual ~BoneHammer();

private:
	typedef Mace super;
};
