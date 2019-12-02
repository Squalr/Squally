#include "Equipable.h"

using namespace cocos2d;

Equipable::Equipable(CurrencyInventory* cost, ItemMeta itemMeta) : super(cost, itemMeta)
{
}

Equipable::~Equipable()
{
}

Vec2 Equipable::getDisplayOffset()
{
	return Vec2::ZERO;
}

std::vector<PlatformerAttack*> Equipable::cloneAssociatedAttacks()
{
	return std::vector<PlatformerAttack*>();
}
