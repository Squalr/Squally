#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class DemonicSword : public Sword
{
public:
	static DemonicSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	DemonicSword();
	virtual ~DemonicSword();

private:
	typedef Sword super;
};
