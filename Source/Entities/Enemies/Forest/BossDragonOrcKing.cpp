#include "BossDragonOrcKing.h"

BossDragonOrcKing* BossDragonOrcKing::create()
{
	BossDragonOrcKing* instance = new BossDragonOrcKing();

	instance->autorelease();

	return instance;
}

BossDragonOrcKing::BossDragonOrcKing() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_BossDragonOrcKing_Animations,
	false)
{
}

BossDragonOrcKing::~BossDragonOrcKing()
{
}
