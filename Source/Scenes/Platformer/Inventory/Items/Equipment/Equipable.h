#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class Equipable : public Item
{
public:
	virtual cocos2d::Vec2 getDisplayOffset();

protected:
	Equipable(CurrencyInventory* cost);
	virtual ~Equipable();

private:
	typedef Item super;
};
