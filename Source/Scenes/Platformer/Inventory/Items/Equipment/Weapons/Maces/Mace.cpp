#include "Mace.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

Mace::Mace(CurrencyInventory* cost, int minAttack, int maxAttack, ItemStats itemStats) : super(cost, minAttack, maxAttack, itemStats)
{
}

Mace::~Mace()
{
}

std::string Mace::getWeaponAttackSound()
{
	return SoundResources::Platformer_Combat_Attacks_Physical_Swings_SwingWeakBlunt2;
}
