#include "Wand.h"

using namespace cocos2d;

Wand::Wand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Wand::~Wand()
{
}
