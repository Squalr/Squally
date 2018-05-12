#include "EvilSnowman.h"

EvilSnowman* EvilSnowman::create()
{
	EvilSnowman* instance = new EvilSnowman();

	instance->autorelease();

	return instance;
}

EvilSnowman::EvilSnowman() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_EvilSnowman_Animations,
	false,
	Size(240.0f, 312.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

EvilSnowman::~EvilSnowman()
{
}
