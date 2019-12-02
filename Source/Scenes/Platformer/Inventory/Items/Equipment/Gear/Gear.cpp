#include "Gear.h"

using namespace cocos2d;

Gear::Gear(CurrencyInventory* cost, int defense, ItemMeta itemMeta) : super(cost, itemMeta)
{
	this->defense = defense;
}

Gear::~Gear()
{
}

int Gear::getDefense()
{
	return this->defense;
}
