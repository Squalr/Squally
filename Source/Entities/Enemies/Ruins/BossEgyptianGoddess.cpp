#include "BossEgyptianGoddess.h"

BossEgyptianGoddess* BossEgyptianGoddess::create()
{
	BossEgyptianGoddess* instance = new BossEgyptianGoddess();

	instance->autorelease();

	return instance;
}

BossEgyptianGoddess::BossEgyptianGoddess() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_BossEgyptianGoddess_Animations,
	false,
	Size(128.0f, 272.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

BossEgyptianGoddess::~BossEgyptianGoddess()
{
}
