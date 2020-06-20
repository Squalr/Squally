#include "Bow.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

Bow::Bow(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Bow::~Bow()
{
}

std::string Bow::getWeaponAttackSound()
{
	return SoundResources::Platformer_Physical_Projectiles_WeaponThrow2;
}
