#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class Katana : public Sword
{
public:
	static Katana* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyKatana;

protected:
	Katana();
	virtual ~Katana();

private:
	typedef Sword super;
};
