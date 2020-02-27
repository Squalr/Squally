#include "Sword.h"

using namespace cocos2d;

Sword::Sword(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Sword::~Sword()
{
}
