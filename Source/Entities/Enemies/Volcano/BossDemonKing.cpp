#include "BossDemonKing.h"

BossDemonKing* BossDemonKing::create()
{
	BossDemonKing* instance = new BossDemonKing();

	instance->autorelease();

	return instance;
}

BossDemonKing::BossDemonKing() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false,
	Size(480.0f, 480.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossDemonKing::~BossDemonKing()
{
}
