#include "BossDragonOrc.h"

BossDragonOrc* BossDragonOrc::create()
{
	BossDragonOrc* instance = new BossDragonOrc();

	instance->autorelease();

	return instance;
}

BossDragonOrc::BossDragonOrc() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossDragonOrc::~BossDragonOrc()
{
}
