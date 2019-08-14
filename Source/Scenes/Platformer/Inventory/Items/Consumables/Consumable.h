#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;
class PlatformerAttack;

class Consumable : public Item
{
public:
	virtual PlatformerAttack* createAssociatedAttack() = 0;

protected:
	Consumable(CurrencyInventory* cost);
	virtual ~Consumable();

private:
	typedef Item super;
};
