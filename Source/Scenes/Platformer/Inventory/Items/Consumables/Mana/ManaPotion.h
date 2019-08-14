#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class ManaPotion : public Consumable
{
public:
	static ManaPotion* create();

	Item* clone() override;
	std::string getItemName() override;
	PlatformerAttack* createAssociatedAttack() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyManaPotion;

protected:
	ManaPotion();
	virtual ~ManaPotion();

private:
	typedef Consumable super;
};
