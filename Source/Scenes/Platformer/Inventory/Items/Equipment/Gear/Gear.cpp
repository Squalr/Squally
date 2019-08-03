#include "Gear.h"

using namespace cocos2d;

Gear::Gear(CurrencyInventory* cost, int defense) : super(cost)
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
