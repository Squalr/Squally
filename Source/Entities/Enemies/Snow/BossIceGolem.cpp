#include "BossIceGolem.h"

BossIceGolem* BossIceGolem::create()
{
	BossIceGolem* instance = new BossIceGolem();

	instance->autorelease();

	return instance;
}

BossIceGolem::BossIceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_BossIceGolem_Animations,
	false)
{
}

BossIceGolem::~BossIceGolem()
{
}
