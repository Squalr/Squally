#include "Bow.h"

using namespace cocos2d;

Bow::Bow(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Bow::~Bow()
{
}
