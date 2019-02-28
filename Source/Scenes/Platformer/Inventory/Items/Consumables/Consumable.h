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

	virtual PlatformerAttack* createAssociatedAttack() = 0;
	virtual ConsumableType getConsumableType() = 0;

protected:
	Consumable();
	virtual ~Consumable();

private:
	typedef Item super;
};
