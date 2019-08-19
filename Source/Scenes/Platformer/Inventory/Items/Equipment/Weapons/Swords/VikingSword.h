#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class VikingSword : public Weapon
{
public:
	static VikingSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyVikingSword;

protected:
	VikingSword();
	~VikingSword();

private:
	typedef Weapon super;
};
