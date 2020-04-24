#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;
class PlatformerAttack;
class PlatformerEntity;

class Consumable : public Item
{
public:
	PlatformerAttack* cloneAssociatedAttack(PlatformerEntity* entity);
	PlatformerAttack* getAssociatedAttack(PlatformerEntity* entity);

	virtual void useOutOfCombat(PlatformerEntity* target);
	bool canUseOutOfCombat();

protected:
	Consumable(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta(), bool outOfCombatUseAllowed = false);
	virtual ~Consumable();

	PlatformerAttack* cloneAssociatedAttack();
	PlatformerAttack* getAssociatedAttack();
	virtual PlatformerAttack* createAssociatedAttack() = 0;

private:
	typedef Item super;

	void bindItemUseCallback(PlatformerAttack* attack, PlatformerEntity* entity);

	PlatformerAttack* associatedAttack;
	bool outOfCombatUseAllowed;
};
