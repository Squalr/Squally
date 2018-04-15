#include "Ghost.h"

Ghost* Ghost::create()
{
	Ghost* instance = new Ghost();

	instance->autorelease();

	return instance;
}

Ghost::Ghost() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Ghost::~Ghost()
{
}
