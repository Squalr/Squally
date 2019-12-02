#include "Offhand.h"

using namespace cocos2d;

Offhand::Offhand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemMeta itemMeta) : super(cost, itemMeta)
{
	this->minAttack = minAttack;
	this->maxAttack = maxAttack;
}

Offhand::~Offhand()
{
}

int Offhand::getMinAttack()
{
	return this->minAttack;
}

int Offhand::getMaxAttack()
{
	return this->maxAttack;
}

float Offhand::getAttackOnset()
{
	return 0.2f;
}

float Offhand::getAttackSustain()
{
	return 0.15f;
}

Vec2 Offhand::getOffhandSizeMultiplier()
{
	return Vec2(1.0f, 1.0f);
}

Vec2 Offhand::getOffhandOffset()
{
	return Vec2::ZERO;
}
