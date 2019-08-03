#include "Equipable.h"

using namespace cocos2d;

Equipable::Equipable(CurrencyInventory* cost) : super(cost)
{
}

Equipable::~Equipable()
{
}

Vec2 Equipable::getDisplayOffset()
{
	return Vec2::ZERO;
}
