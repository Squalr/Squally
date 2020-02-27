#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class Rapier : public Sword
{
public:
	static Rapier* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyRapier;

protected:
	Rapier();
	virtual ~Rapier();

private:
	typedef Sword super;
};
