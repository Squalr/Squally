#include "BossWitch.h"

const std::string BossWitch::KeyEnemyBossWitch = "boss_witch";

BossWitch* BossWitch::create()
{
	BossWitch* instance = new BossWitch();

	instance->autorelease();

	return instance;
}

BossWitch::BossWitch() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_BossWitch_Animations,
	false,
	Size(360.0f, 420.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

BossWitch::~BossWitch()
{
}
