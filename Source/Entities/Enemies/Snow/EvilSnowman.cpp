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
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

EvilSnowman::~EvilSnowman()
{
}
