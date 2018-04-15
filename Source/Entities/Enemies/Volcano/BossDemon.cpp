#include "BossDemon.h"

BossDemon* BossDemon::create()
{
	BossDemon* instance = new BossDemon();

	instance->autorelease();

	return instance;
}

BossDemon::BossDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BossDemon::~BossDemon()
{
}
