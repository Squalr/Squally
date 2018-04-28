#include "BossRhinoman.h"

BossRhinoman* BossRhinoman::create()
{
	BossRhinoman* instance = new BossRhinoman();

	instance->autorelease();

	return instance;
}

BossRhinoman::BossRhinoman() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

BossRhinoman::~BossRhinoman()
{
}
