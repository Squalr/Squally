#include "EggProjectile.h"

EggProjectile* EggProjectile::create()
{
	EggProjectile* eggProjectile = new EggProjectile();

	eggProjectile->autorelease();

	return eggProjectile;
}

EggProjectile::EggProjectile()
{
}

EggProjectile::~EggProjectile()
{
}
