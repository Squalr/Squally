#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class Harbinger : public Sword
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
	typedef Sword super;
};
