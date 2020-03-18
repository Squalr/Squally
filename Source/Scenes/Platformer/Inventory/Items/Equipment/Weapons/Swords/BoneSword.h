#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class BoneSword : public Sword
{
public:
	static BoneSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBoneSword;

protected:
	BoneSword();
	virtual ~BoneSword();

private:
	typedef Sword super;
};
