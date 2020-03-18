#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/Mace.h"

class VoidMace : public Mace
{
public:
	static VoidMace* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyVoidMace;

protected:
	VoidMace();
	virtual ~VoidMace();

private:
	typedef Mace super;
};
