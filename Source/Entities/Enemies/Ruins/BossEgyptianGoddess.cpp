#include "BossEgyptianGoddess.h"

BossEgyptianGoddess* BossEgyptianGoddess::create()
{
	BossEgyptianGoddess* instance = new BossEgyptianGoddess();

	instance->autorelease();

	return instance;
}

BossEgyptianGoddess::BossEgyptianGoddess() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_BossEgyptianGoddess_Animations,
	false)
{
}

BossEgyptianGoddess::~BossEgyptianGoddess()
{
}
