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

float Weapon::getAttackOnset()
{
	return 0.2f;
}

float Weapon::getAttackSustain()
{
	return 0.15f;
}

Vec2 Weapon::getWeaponSizeMultiplier()
{
	return Vec2(1.0f, 1.0f);
}

Vec2 Weapon::getWeaponOffset()
{
	return Vec2::ZERO;
}
