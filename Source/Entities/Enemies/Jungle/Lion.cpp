#include "Lion.h"

Lion* Lion::create()
{
	Lion* instance = new Lion();

	instance->autorelease();

	return instance;
}

Lion::Lion() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Lion::~Lion()
{
}
