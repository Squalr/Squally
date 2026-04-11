#include "Mace.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

Mace::Mace(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Mace::~Mace()
{
}

Vec2 Mace::getWeaponCollisionOffset()
{
	return Vec2(0.0f, 54.0f);
}

std::string Mace::getWeaponAttackSound()
{
	return SoundResources::Platformer_Physical_Swings_SwingWeakBlunt2;
}

std::string Mace::getWeaponImpactSound()
{
	return SoundResources::Platformer_Physical_Impact_HitHeavy1;
}
