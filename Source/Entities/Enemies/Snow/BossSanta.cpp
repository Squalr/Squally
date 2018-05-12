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
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossSanta::~BossSanta()
{
}
