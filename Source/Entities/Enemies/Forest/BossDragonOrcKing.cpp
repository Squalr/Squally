#include "BossDragonOrcKing.h"

BossDragonOrcKing* BossDragonOrcKing::create()
{
	BossDragonOrcKing* instance = new BossDragonOrcKing();

	instance->autorelease();

	return instance;
}

BossDragonOrcKing::BossDragonOrcKing() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_BossDragonOrcKing_Animations,
	false,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossDragonOrcKing::~BossDragonOrcKing()
{
}
