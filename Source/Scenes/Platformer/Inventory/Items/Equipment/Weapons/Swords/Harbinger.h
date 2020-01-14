#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Harbinger : public Weapon
{
public:
	static Harbinger* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHarbinger;

protected:
	Harbinger();
	virtual ~Harbinger();

private:
	typedef Weapon super;
};
