#include "Wand.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

Wand::Wand(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Wand::~Wand()
{
}

std::string Wand::getWeaponAttackSound()
{
	return SoundResources::Platformer_Physical_Swings_SwingWeakHybrid2;
}
