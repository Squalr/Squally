#include "Equipable.h"

using namespace cocos2d;

Equipable::Equipable(CurrencyInventory* cost, ItemStats itemStats, ItemMeta itemMeta) : super(cost, itemMeta)
{
	this->itemStats = itemStats;
}

Equipable::~Equipable()
{
}

Equipable::ItemStats Equipable::getItemStats()
{
	return this->itemStats;
}

Vec2 Equipable::getDisplayOffset()
{
	return Vec2::ZERO;
}

std::vector<PlatformerAttack*> Equipable::cloneAssociatedAttacks()
{
	return std::vector<PlatformerAttack*>();
}
