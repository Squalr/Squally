#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class VoidSword : public Sword
{
public:
	static VoidSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyVoidSword;

protected:
	VoidSword();
	virtual ~VoidSword();

private:
	typedef Sword super;
};
