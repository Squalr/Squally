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
		int attackBonus;
		int magicAttackBonus;
		int armorBonus;
		float speedBonus;

		ItemStats() : healthBonus(0), manaBonus(0), attackBonus(0), magicAttackBonus(0), armorBonus(0), speedBonus(0.0f) { }
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
