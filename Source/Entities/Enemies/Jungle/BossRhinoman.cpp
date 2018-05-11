#include "BossRhinoman.h"

BossRhinoman* BossRhinoman::create()
{
	BossRhinoman* instance = new BossRhinoman();

	instance->autorelease();

	return instance;
}

BossRhinoman::BossRhinoman() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_BossRhinoman_Animations,
	false)
{
}

BossRhinoman::~BossRhinoman()
{
}
