#include "RedDragon1.h"

RedDragon1* RedDragon1::create()
{
	RedDragon1* instance = new RedDragon1();

	instance->autorelease();

	return instance;
}

RedDragon1::RedDragon1() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

RedDragon1::~RedDragon1()
{
}
