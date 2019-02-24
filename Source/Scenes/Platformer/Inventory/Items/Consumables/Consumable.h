#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;
class PlatformerAttack;

class Consumable : public Item
{
public:
	enum ConsumableType
	{
		Buff,
		Debuff,
		Either
	};

	PlatformerAttack* getAssociatedAttack();
	virtual ConsumableType getConsumableType() = 0;

protected:
	Consumable();
	virtual ~Consumable();

	PlatformerAttack* associatedAttack;

private:
	typedef Item super;
};
