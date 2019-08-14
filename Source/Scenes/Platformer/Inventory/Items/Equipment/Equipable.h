#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;
class PlatformerAttack;

class Equipable : public Item
{
public:
	virtual cocos2d::Vec2 getDisplayOffset();
	virtual std::vector<PlatformerAttack*> cloneAssociatedAttacks();

protected:
	Equipable(CurrencyInventory* cost);
	virtual ~Equipable();

private:
	typedef Item super;
};
