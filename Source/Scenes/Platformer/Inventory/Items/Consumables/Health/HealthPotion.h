#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class HealthPotion : public Consumable
{
public:
	static HealthPotion* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHealthPotion;

protected:
	HealthPotion();
	~HealthPotion();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};
