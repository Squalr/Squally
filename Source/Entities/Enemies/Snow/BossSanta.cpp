#include "BossSanta.h"

BossSanta* BossSanta::create()
{
	BossSanta* instance = new BossSanta();

	instance->autorelease();

	return instance;
}

BossSanta::BossSanta() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_BossSanta_Animations,
	false)
{
}

BossSanta::~BossSanta()
{
}
