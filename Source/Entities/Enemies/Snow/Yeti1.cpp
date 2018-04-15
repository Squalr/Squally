#include "Yeti1.h"

Yeti1* Yeti1::create()
{
	Yeti1* instance = new Yeti1();

	instance->autorelease();

	return instance;
}

Yeti1::Yeti1() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Yeti1::~Yeti1()
{
}
