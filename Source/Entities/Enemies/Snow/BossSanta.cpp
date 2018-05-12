#include "BossSanta.h"

BossSanta* BossSanta::create()
{
	BossSanta* instance = new BossSanta();

	instance->autorelease();

	return instance;
}

BossSanta::BossSanta() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_BossSanta_Animations,
	false,
	Size(240.0f, 312.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossSanta::~BossSanta()
{
}
