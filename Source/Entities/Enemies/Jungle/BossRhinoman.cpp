#include "BossRhinoman.h"

const std::string BossRhinoman::KeyEnemyBossRhinoman = "boss_rhinoman";

BossRhinoman* BossRhinoman::create()
{
	BossRhinoman* instance = new BossRhinoman();

	instance->autorelease();

	return instance;
}

BossRhinoman::BossRhinoman() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_BossRhinoman_Animations,
	false,
	Size(592.0f, 592.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossRhinoman::~BossRhinoman()
{
}
