#include "Penguin2.h"

Penguin2* Penguin2::create()
{
	Penguin2* instance = new Penguin2();

	instance->autorelease();

	return instance;
}

Penguin2::Penguin2() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Penguin2::~Penguin2()
{
}
