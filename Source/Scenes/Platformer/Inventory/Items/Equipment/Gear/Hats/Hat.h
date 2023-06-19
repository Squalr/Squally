#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Gear.h"

#define ARCHER_HP(tier) tier / 2 + 1
#define ARCHER_MP(tier) tier / 2 + 1
#define ARCHER_ATTACK(tier) (int)std::ceil((float)tier * 2.0f / 3.0f)
#define ARCHER_MAGIC_ATTACK(tier) (int)std::ceil((float)tier / 3.0f)
#define ARCHER_ARMOR(tier) tier
#define ARCHER_SPEED(tier) 0.035f + 0.005f * (float)tier

#define MAGE_HP(tier) 0
#define MAGE_MP(tier) tier
#define MAGE_ATTACK(tier) 0
#define MAGE_MAGIC_ATTACK(tier) tier + 1
#define MAGE_ARMOR(tier) tier / 2
#define MAGE_SPEED(tier) 0.025f + 0.005f * (float)tier

#define WARRIOR_HP(tier) tier
#define WARRIOR_MP(tier) tier / 4
#define WARRIOR_ATTACK(tier) tier + 1
#define WARRIOR_MAGIC_ATTACK(tier) 0
#define WARRIOR_ARMOR(tier) tier + 1
#define WARRIOR_SPEED(tier) 0.025f + 0.005f * (float)tier

class Hat : public Gear
{
public:

protected:
	Hat(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Hat();

private:
	typedef Gear super;
};
