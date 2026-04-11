#include "Wand.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

Wand::Wand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Wand::~Wand()
{
}

Vec2 Wand::getWeaponCollisionOffset()
{
	return Vec2(0.0f, 26.0f);
}

std::string Wand::getWeaponAttackSound()
{
	return SoundResources::Platformer_Physical_Swings_SwingWeakHybrid2;
}

std::string Wand::getWeaponImpactSound()
{
	return SoundResources::Platformer_Physical_Impact_HitSoft2;
}

