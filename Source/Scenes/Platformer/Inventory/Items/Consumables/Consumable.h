#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;
class PlatformerAttack;

class Consumable : public Item
{
public:
	PlatformerAttack* cloneAssociatedAttack();
	PlatformerAttack* getAssociatedAttack();

protected:
	Consumable(CurrencyInventory* cost);
	~Consumable();

	virtual PlatformerAttack* createAssociatedAttack() = 0;

private:
	typedef Item super;

	PlatformerAttack* associatedAttack;
};
