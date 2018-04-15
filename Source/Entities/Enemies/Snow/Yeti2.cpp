#include "Yeti2.h"

Yeti2* Yeti2::create()
{
	Yeti2* instance = new Yeti2();

	instance->autorelease();

	return instance;
}

Yeti2::Yeti2() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Yeti2::~Yeti2()
{
}
