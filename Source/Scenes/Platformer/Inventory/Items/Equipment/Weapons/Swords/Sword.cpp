#include "Sword.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

Sword::Sword(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Sword::~Sword()
{
}

std::string Sword::getWeaponAttackSound()
{
	return SoundResources::Platformer_Physical_Swings_SwingWeakBlade5;
}
