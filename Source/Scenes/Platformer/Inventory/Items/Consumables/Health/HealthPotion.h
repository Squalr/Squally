#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class HealthPotion : public Consumable
{
public:
	static HealthPotion* create();

	Item* clone() override;
	PlatformerAttack* createAssociatedAttack() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	ConsumableType getConsumableType() override;

	static const std::string SaveKeyHealthPotion;

protected:
	HealthPotion();
	virtual ~HealthPotion();

private:
	typedef Consumable super;
};
