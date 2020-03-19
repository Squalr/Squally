#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class ManaPotion : public Consumable
{
public:
	static ManaPotion* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;
	static const float RestorePercentage;

protected:
	ManaPotion();
	virtual ~ManaPotion();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};
