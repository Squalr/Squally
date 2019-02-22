#include "Weapon.h"

using namespace cocos2d;

Weapon::Weapon(LocalizedString* name, std::string iconResource, int minAttack, int maxAttack) : super(name, iconResource)
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
