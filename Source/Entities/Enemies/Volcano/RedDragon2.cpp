#include "RedDragon2.h"

RedDragon2* RedDragon2::create()
{
	RedDragon2* instance = new RedDragon2();

	instance->autorelease();

	return instance;
}

RedDragon2::RedDragon2() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

RedDragon2::~RedDragon2()
{
}
