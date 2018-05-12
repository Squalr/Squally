#include "BossIceGolem.h"

BossIceGolem* BossIceGolem::create()
{
	BossIceGolem* instance = new BossIceGolem();

	instance->autorelease();

	return instance;
}

BossIceGolem::BossIceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_BossIceGolem_Animations,
	false,
	Size(240.0f, 312.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossIceGolem::~BossIceGolem()
{
}
