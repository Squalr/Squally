#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class RestorePotion : public Consumable
{
public:
	static RestorePotion* create();

	Item* clone() override;
	std::string getItemName() override;
	PlatformerAttack* createAssociatedAttack() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyRestorePotion;

protected:
	RestorePotion();
	virtual ~RestorePotion();

private:
	typedef Consumable super;
};
