#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class HealthPotion : public Consumable
{
public:
	HealthPotion* create();

protected:
	HealthPotion();
	virtual ~HealthPotion();

private:
	typedef Consumable super;
};
