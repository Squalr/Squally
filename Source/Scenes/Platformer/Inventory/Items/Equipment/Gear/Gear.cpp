#include "Gear.h"

using namespace cocos2d;

Gear::Gear(int defense) : super()
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
