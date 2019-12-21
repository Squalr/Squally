#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class Offhand : public Equipable
{
public:
	int getMinAttack();
	int getMaxAttack();
	virtual float getAttackOnset();
	virtual float getAttackSustain();
	virtual cocos2d::Vec2 getOffhandSizeMultiplier();
	virtual cocos2d::Vec2 getOffhandOffset();

protected:
	Offhand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats, ItemMeta itemMeta = ItemMeta());
	virtual ~Offhand();

private:
	typedef Equipable super;

	int minAttack;
	int maxAttack;
};
