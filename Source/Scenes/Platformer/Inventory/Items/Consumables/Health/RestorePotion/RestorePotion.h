#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class RestorePotion : public Consumable
{
public:
	static RestorePotion* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyRestorePotion;
	static const int HealTicks;

protected:
	RestorePotion();
	virtual ~RestorePotion();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};
