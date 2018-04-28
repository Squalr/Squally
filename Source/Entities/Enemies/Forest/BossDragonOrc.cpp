#include "BossDragonOrc.h"

BossDragonOrc* BossDragonOrc::create()
{
	BossDragonOrc* instance = new BossDragonOrc();

	instance->autorelease();

	return instance;
}

BossDragonOrc::BossDragonOrc() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

BossDragonOrc::~BossDragonOrc()
{
}
