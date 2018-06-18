#include "BossIceGolem.h"

const std::string BossIceGolem::KeyEnemyBossIceGolem = "boss_ice_golem";

BossIceGolem* BossIceGolem::create()
{
	BossIceGolem* instance = new BossIceGolem();

	instance->autorelease();

	return instance;
}

BossIceGolem::BossIceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_BossIceGolem_Animations,
	false,
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossIceGolem::~BossIceGolem()
{
}
