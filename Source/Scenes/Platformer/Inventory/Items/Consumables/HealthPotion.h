#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class HealthPotion : public Item
{
public:
	HealthPotion* create();

protected:
	HealthPotion();
	virtual ~HealthPotion();

private:
	typedef Item super;
};
