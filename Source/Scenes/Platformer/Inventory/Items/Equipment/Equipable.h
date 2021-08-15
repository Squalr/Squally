#pragma once

#include "Engine/Inventory/Item.h"

class PlatformerAttack;

class Equipable : public Item
{
public:
	struct ItemStats
	{
		int healthBonus = 0;
		int manaBonus = 0;
		int attackBonus = 0;
		int magicAttackBonus = 0;
		int armorBonus = 0;
		float speedBonus = 0.0f;

		ItemStats() { }
		ItemStats(int healthBonus, int manaBonus, int attackBonus, int magicAttackBonus, int armorBonus, float speedBonus)
			: healthBonus(healthBonus), manaBonus(manaBonus), attackBonus(attackBonus), magicAttackBonus(magicAttackBonus), armorBonus(armorBonus), speedBonus(speedBonus) { }
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
