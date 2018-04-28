#include "BossGoddess.h"

BossGoddess* BossGoddess::create()
{
	BossGoddess* instance = new BossGoddess();

	instance->autorelease();

	return instance;
}

BossGoddess::BossGoddess() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

BossGoddess::~BossGoddess()
{
}
