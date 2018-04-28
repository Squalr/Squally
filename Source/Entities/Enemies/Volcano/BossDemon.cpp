#include "BossDemon.h"

BossDemon* BossDemon::create()
{
	BossDemon* instance = new BossDemon();

	instance->autorelease();

	return instance;
}

BossDemon::BossDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false,
	Size(480.0f, 480.0f),
	0.6f,
	Vec2(0.0f, -112.0f))
{
}

BossDemon::~BossDemon()
{
}
