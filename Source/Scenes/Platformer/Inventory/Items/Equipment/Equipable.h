#pragma once

#include "Engine/Inventory/Item.h"

class PlatformerAttack;

class Equipable : public Item
{
public:
	struct ItemStats
	{
		int healthBonus;
		int manaBonus;
		int armorBonus;
		int attackBonus;
		float speedBonus;

		ItemStats() : healthBonus(0), manaBonus(0), armorBonus(0), attackBonus(0), speedBonus(0) { }
		ItemStats(int healthBonus, int manaBonus, int armorBonus, int attackBonus, float speedBonus)
			: healthBonus(healthBonus), manaBonus(manaBonus), armorBonus(armorBonus), attackBonus(attackBonus), speedBonus(speedBonus) { }
	};

	ItemStats getItemStats();
	virtual cocos2d::Vec2 getDisplayOffset();
	virtual std::vector<PlatformerAttack*> cloneAssociatedAttacks();

protected:
	Equipable(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Equipable();

private:
	typedef Item super;

	ItemStats itemStats;
};
