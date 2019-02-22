#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class HealthPotion : public Consumable
{
public:
	static HealthPotion* create();

	std::string getSerializationKey() override;

	static const std::string SaveKeyHealthPotion;

protected:
	HealthPotion();
	virtual ~HealthPotion();

private:
	typedef Consumable super;
};
