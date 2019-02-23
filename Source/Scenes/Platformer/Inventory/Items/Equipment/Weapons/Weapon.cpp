#include "Weapon.h"

using namespace cocos2d;

Weapon::Weapon(int minAttack, int maxAttack) : super()
{
	this->minAttack = minAttack;
	this->maxAttack = maxAttack;
}

Weapon::~Weapon()
{
}

int Weapon::getMinAttack()
{
	return this->minAttack;
}

int Weapon::getMaxAttack()
{
	return this->maxAttack;
}
